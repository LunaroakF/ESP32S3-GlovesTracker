// ADC口串联的电阻大小，对于ESP8266电位器链接3.3V要保证传入ADC分压在1V以内
// ||仅标记无引用||
#define OHM 23.5

#define NO_THUMB false  // 是否禁用大拇指追踪
#define FLIP_POTS false  // 是否反转电位器

#define MAINTHREAD_DELAY 4  // 主线程延迟时间ms
#define MULTIPLEXER_DELAY 100  // 复用器稳定时间us

#define CALIBRATION_LOOPS \
	-1  // -1表示不进行校准，0表示只进行一次校准，正数表示进行多次校准
#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

#define PHASE 0  // ADC相位偏移量

// 手势
#define TRIGGER_GESTURE true  // 触发手势
#define GRAB_GESTURE true  // 抓取手势
#define PINCH_GESTURE true  // 捏合手势

// 开发板定义
#define BOARD ESP8266
#define SERIAL_BAUD_RATE 115200  // 串口波特率
#define COMMUNICATION COMM_WIFISERIAL  // 通信方式 COMM_SERIAL | COMM_WIFISERIAL

// 编码方式 ENCODING_ALPHA |COMMUNICATION ENCODING_LEGACY(已弃用)
#define ENCODING ENCODING_ALPHA

// 中值滤波
#define ENABLE_MEDIAN_FILTER true
#ifdef ENABLE_MEDIAN_FILTER
#define MEDIAN_SAMPLES 40  // 中值滤波采样次数
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
#define PIN_SC 12
#define PIN_ADC A0
#define ANALOG_MAX 1023  // ADC最大值
#endif