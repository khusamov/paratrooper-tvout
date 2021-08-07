CHANGELOG
=========

18-07-2021
----------
Исправили ошибку библиотеки EncButton
https://github.com/GyverLibs/EncButton/issues/2

16-07-2021
----------
Добавил флаг build_unflags = -flto в файле platformio.ini, чтобы избежать ошибок библиотеки TVOut вида:

Linking .pio\build\uno\firmware.elf
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s: Assembler messages:
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:518: Error: unknown opcode `delay2'
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:557: Error: unknown opcode `delay1'
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:559: Error: unknown opcode `delay2'
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:562: Error: unknown opcode `delay2'
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:565: Error: unknown opcode `delay2'
...
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:714: Error: unknown opcode `svprt'
C:\Users\khusamov\AppData\Local\Temp\cc4hDYOb.s:716: Error: unknown opcode `o1bs'
lto-wrapper.exe: fatal error: avr-g++ returned 1 exit status
compilation terminated.
c:/users/khusamov/.platformio/packages/toolchain-atmelavr/bin/../lib/gcc/avr/5.4.0/../../../../avr/bin/ld.exe: error: lto-wrapper failed
collect2.exe: error: ld returned 1 exit status
*** [.pio\build\uno\firmware.elf] Error 1