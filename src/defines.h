// ADC口串联的电阻大小，对于ESP8266电位器链接3.3V要保证传入ADC分压在1V以内
// ||仅标记无引用||
#define OHM 23.5

// 是否禁用大拇指
#define NO_THUMB false

// 主线程延迟时间
#define MAINTHREAD_DELAY 4  // ms
#define CALIBRATION_LOOPS \
	-1  // How many loops should be calibrated. Set to -1 to always be calibrated.
#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

// ADC相位偏移量
#define PHASE 0

// 开发板定义
#define BOARD ESP8266
#define SERIAL_BAUD_RATE 115200  // 串口波特率
#define COMMUNICATION COMM_SERIAL  // 通信方式 COMM_SERIAL | COMM_WIFISERIAL

// 编码方式 ENCODING_ALPHA | ENCODING_LEGACY(已弃用)
#define ENCODING ENCODING_ALPHA

// 是否启用中值滤波
#define ENABLE_MEDIAN_FILTER true
#ifdef ENABLE_MEDIAN_FILTER
#define MEDIAN_SAMPLES 50  // 中值滤波采样次数
#endif

// 是否对模拟输入值限幅
#define CLAMP_ANALOG_MAP true  // 把经过map()映射后的模拟值限制在0到ANALOG_MAX之间

// 启用并设置最小值和最大值，以匹配传感器的预期原始值范围，这将丢弃有用范围之外的任何无用值
#define CLAMP_FLEXION false  // 是否对原始值限幅
#define CLAMP_MIN 0  // 限幅最小值
#define CLAMP_MAX ANALOG_MAX  // 限幅最大值

// 引脚定义
#if BOARD == ESP8266
#define PIN_SA 13
#define PIN_SB 14
#define PIN_SC 15
#define PIN_ADC A0
#define ANALOG_MAX 1023  // ADC最大值
#endif