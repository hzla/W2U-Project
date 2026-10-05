.syntax unified
.thumb
.section .text

@ Replay the reviewed first eight bytes displaced by each function hook.
@ Native continuations retain their original stack frame and return normally.
.global ClientWeatherStart_Original
.type ClientWeatherStart_Original, %function
.thumb_func
ClientWeatherStart_Original:
    push {r4-r6, lr}
    adds r6, r0, #0
    ldr r0, [r2]
    adds r5, r1, #0
    ldr r3, =0x021B78B5
    bx r3
    .size ClientWeatherStart_Original, . - ClientWeatherStart_Original

.global ClientWeatherEnd_Original
.type ClientWeatherEnd_Original, %function
.thumb_func
ClientWeatherEnd_Original:
    push {r3-r5, lr}
    adds r5, r1, #0
    adds r4, r0, #0
    ldr r0, [r5]
    ldr r3, =0x021B7935
    bx r3
    .size ClientWeatherEnd_Original, . - ClientWeatherEnd_Original
