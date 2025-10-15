#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"
#include "math.h"

extern osMessageQId position_command_queueHandle;
extern osMessageQId motor_feedback_queueHandle;
extern CAN_HandleTypeDef hcan1;

typedef struct {
    float plant;
    float target;
    float error;
    float prev_error;

    float kp;
    float ki;
    float kd;
    float max_out;
    float min_out;

    float p_out;
    float i_out;
    float d_out;
    float total_out;
} PID_t;


void calc_pid(PID_t *pid, float plant, float target, float dt) {
    pid->plant = plant;
    pid->target = target;

    pid->prev_error = pid->error;
    pid->error = target - plant;

    pid->p_out = pid->error * pid->kp;
    pid->i_out += pid->error * pid->ki * dt;
    pid->d_out = (pid->error - pid->prev_error) * pid->kd / dt;

    pid->total_out = pid->p_out + pid->i_out + pid->d_out;

    if (pid->total_out > pid->max_out) pid->total_out = pid->max_out;
    if (pid->total_out < pid->min_out) pid->total_out = pid->min_out;
}

void send_motor_command(int32_t d2) {
    CAN_TxHeaderTypeDef tx_header;
    uint8_t tx_data[8];
    memset(tx_data, 0, sizeof(uint8_t) * 8);

    tx_header.StdId = 0x1FF;
    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 0x08;

    tx_data[2] = d2 >> 8;
    tx_data[3] = d2;

    HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data,
                            (uint32_t*) CAN_TX_MAILBOX0);
}

static PID_t motor_pid;
static MotorFeedback_t motor_feedback;
static uint8_t position_target;

void motor_control_task(void const * argument) {
    (void) argument;
    const size_t delay_ms = 1;
    TickType_t delay_ticks = pdMS_TO_TICKS(delay_ms);

    position_target = 0;
    memset(&motor_pid, 0, sizeof(PID_t));
    motor_pid.kp = 150;
    motor_pid.ki = 10;
    motor_pid.kd = 2;
    motor_pid.max_out = 15000;
    motor_pid.min_out = -15000;
    memset(&motor_feedback, 0, sizeof(MotorFeedback_t));

    while (1) {
        uint8_t new_position_target;
        BaseType_t res = xQueueReceive(position_command_queueHandle, &new_position_target, 0);
        if (res == pdPASS) {
            position_target = new_position_target;
        }

        xQueueReceive(motor_feedback_queueHandle, &motor_feedback, 0);

        float position = ((float) (motor_feedback.encoder_angle)) / 8192 * 360;

        float cw = fabs(fmodf(position_target - position + 360, 360));
        float ccw = fabs(fmodf(position - position_target + 360, 360));

        float rel_position = fmin(cw, ccw) == cw ? -cw : ccw;

        calc_pid(&motor_pid, rel_position, 0, ((float) (delay_ms)) / 1000);

        send_motor_command(motor_pid.total_out);

        vTaskDelay(delay_ticks);
    }
}
