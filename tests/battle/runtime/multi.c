/* Test-only native four-party setup adapter; never packaged in a release ROM. */
#include <stdint.h>

/* The fixture pins the complete US W2 routines before installing this hook.
 * Trainer IDs are consecutive: opponent, AI partner, second opponent.
 * Use the native seven-argument setup, not handcrafted battle parameters. */
void W2UTest_SetMultiTrainer(void *battle, void *data, void *situation,
                            uint16_t opponent, uint32_t heap)
{
    typedef void (*Setup)(void *, void *, void *, uint16_t, uint16_t,
                         uint16_t, uint32_t);
    ((Setup)0x020183b1)(battle, data, situation, (uint16_t)(opponent + 1),
                      opponent, (uint16_t)(opponent + 2), heap);
}
