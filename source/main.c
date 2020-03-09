#include <stdio.h>
#include "numpy_types.h"
#include "ei_classifier_porting.h"
#include "ei_classifier_types.h"

// Replace the features below with raw features from 'Live classification'
static float features[] = {
    -2.1100, 9.9400, -0.0700, -2.7300, 13.3600, 1.0200, -1.9300, 11.5800, 0.9700, -1.7700, 8.8500, -0.3200, -1.7700, 8.8500, -0.3200, -1.9800, 8.0400, -1.3600, -2.3400, 9.3900, -1.4400, -2.4900, 10.4700, -0.6200, -2.2800, 10.7800, 0.1100, -1.8100, 10.2300, -0.0200, -1.5200, 9.1700, -0.6700, -1.5200, 9.1700, -0.6700, -1.5500, 9.1700, -0.6900, -1.8900, 10.3200, -0.3800, -1.7700, 11.0000, -0.1500, -1.0000, 11.0800, -0.4100, -0.5200, 11.6100, -0.8200, -0.5600, 13.4400, -1.3900, -0.7800, 16.2000, -1.6500, -0.7800, 16.2000, -1.6500, -0.8200, 18.7100, -0.4900, -1.0700, 19.8000, 0.6400, -1.7700, 19.9700, 1.1900, -2.1700, 19.4000, 1.3000, -1.9500, 17.5600, 1.3700, -1.5000, 15.1300, 1.2900, -1.5000, 15.1300, 1.2900, -0.8600, 12.7200, 1.1400, -0.8900, 11.3300, 0.8700, -0.9800, 10.3500, 0.7300, -0.8800, 9.4700, 0.9800, -0.5100, 8.5900, 0.9600, -0.1000, 7.8400, 0.7500, -0.1000, 7.8400, 0.7500, 0.1500, 7.2300, 0.6400, 0.4800, 6.4000, 0.4000, 1.0000, 6.1600, 0.1800, 1.8300, 5.4100, 0.1200, 2.5600, 4.7600, 0.0800, 3.0700, 4.5800, -0.0400, 3.4700, 5.0300, 0.0000, 3.4700, 5.0300, 0.0000, 4.0400, 4.7900, 0.1100, 4.6100, 4.6400, 0.3600, 5.0200, 4.7200, 0.2900, 5.7100, 4.3900, 0.4300, 5.8500, 4.6000, 0.7600, 6.0900, 4.8300, 0.7300, 6.0900, 4.8300, 0.7300, 6.9000, 4.1600, 0.4700, 7.4500, 3.6600, 0.4200, 7.8000, 3.5700, 0.6100, 7.7900, 3.6300, 0.7200, 7.7200, 3.7600, 0.4300, 8.1200, 3.3100, 0.5900, 8.3800, 3.0900, 0.8300, 8.3800, 3.0900, 0.8300, 8.7200, 2.9900, 0.8600, 8.5400, 3.4700, 0.5800, 8.3900, 3.7400, 0.5300, 8.6700, 3.8400, 0.8600, 8.8800, 3.4200, 0.9900, 9.1100, 3.2600, 0.7900, 9.1100, 3.2600, 0.7900, 9.0300, 3.2900, 0.6100, 8.8500, 3.5000, 0.6700, 9.0400, 3.1600, 0.6900, 9.1400, 3.0100, 0.9100, 9.5000, 2.4900, 0.9000, 9.6200, 2.0300, 0.6800, 9.6200, 2.0300, 0.6800, 9.4400, 1.9400, 0.5200, 9.3300, 1.9000, 0.4500, 9.7400, 1.8800, 0.7700, 9.7900, 2.0300, 1.1800, 9.9200, 1.8300, 1.0700, 9.9400, 1.3600, 0.7400, 9.5800, 0.8900, 0.4900, 9.5800, 0.8900, 0.4900, 9.1800, 0.5200, 0.1800, 9.4600, -0.8300, 0.2500, 9.3100, -2.0000, 0.5900, 8.7000, -2.6300, 0.6700, 7.8500, -2.5200, 0.4700, 6.4600, -1.6100, 0.1600, 6.4600, -1.6100, 0.1600, 4.9900, -0.5300, -0.1100, 4.1300, 1.1100, 0.0000, 3.5400, 2.9800, 0.6100, 2.5000, 3.7700, 0.7900, -0.3000, 7.0500, -0.3600, -0.3400, 7.4300, -1.8500, -0.3400, 7.4300, -1.8500, 0.0900, 7.2800, -1.8600, 1.5800, 6.2100, -1.0100, 2.8900, 5.4500, 1.2400, 1.5500, 7.0600, 0.9400, 0.2000, 8.7600, -0.1500, -0.5000, 7.5200, -0.2500, -2.0100, 8.7400, 0.4500, -2.0100, 8.7400, 0.4500, -1.8900, 11.5900, -0.3600, -2.2400, 13.6300, -0.3800, -2.6600, 14.8800, -0.0700, -2.1200, 15.2000, -0.5300, -2.1400, 16.2700, -0.2600, -2.0400, 16.9000, 0.0400, -2.0400, 16.9000, 0.0400, -1.4900, 15.9500, 1.0900, -1.0100, 15.3600, 1.9300, -0.9200, 14.7200, 2.1000, -1.3100, 14.4100, 0.9800, -1.0100, 12.9300, 0.3500, -1.0200, 12.5700, 0.4200, -1.0400, 12.2300, 0.8800, -1.0400, 12.2300, 0.8800, -2.3500, 17.0900, 2.5700, -2.8400, 18.4800, 2.4900, 0.6800, 9.1400, -0.7600, 0.6800, 5.5300, -0.0200, -0.3800, 6.9800, 0.2000, -1.2000, 8.2900, 0.1700, -1.2000, 8.2900, 0.1700, -1.6800, 8.6500, 1.0900, -2.7600, 11.5600, 1.8900
};

int get_feature_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

EI_IMPULSE_ERROR run_classifier(signal_t *, ei_impulse_result_t *, bool);
int signal_from_buffer(float *data, size_t data_size, signal_t *signal);

int main() {
    signal_t signal;
    signal.total_length = sizeof(features) / sizeof(features[0]);
    signal.get_data = &get_feature_data;

    ei_impulse_result_t result;

    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, true);
    printf("run_classifier returned: %d\n", res);

    printf("Begin output\n");

    // print the predictions
    printf("[");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        printf("%.5f", result.classification[ix].value);
#if EI_CLASSIFIER_HAS_ANOMALY == 1
        printf(", ");
#else
        if (ix != EI_CLASSIFIER_LABEL_COUNT - 1) {
            printf(", ");
        }
#endif
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    printf("%.3f", result.anomaly);
#endif
    printf("]\n");

    printf("End output\n");
}
