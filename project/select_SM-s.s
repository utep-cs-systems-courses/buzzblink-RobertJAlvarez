  .arch msp430g2553
  .p2align 1,0
  .text
jt: .word default
    .word case1
    .word case2
    .word case3
    .word case4

  .global select_SM
  .extern n_switch_down

select_SM:
  ;; if (n_switch_down > 4) goto default
  cmp #4, n_switch_down
  jnc default
  ;; PC = jt[n_switch_down]
  mov &n_switch_down, r12
  add r12, r12
  mov jt(r12), r0
case1:
  call #led_pattern_state_machine
  jmp out
case2:
  call #dimming_state_machines
  jmp out
case3:
  call #high_to_low_buzzer
  jmp out
case4:
default:
  call #off_leds_buzzer
out:
  pop r0
