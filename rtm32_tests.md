# RTM32 - Tests de Instrucciones (STX4)

---

# Caso 1
## Descripción
`ADD` — suma de dos registros.

## Precondiciones
- `$t1` = `0x00000005`
- `$t2` = `0x00000003`

## Code
```asm
ADD $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000008`

## Conclusiones
Anduvo. 5 + 3 = 8 en `$t0`.

---

# Caso 2
## Descripción
`SUB` — resta. Resultado negativo en complemento a dos.

## Precondiciones
- `$t1` = `0x00000003`
- `$t2` = `0x00000007`

## Code
```asm
SUB $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0xFFFFFFFC`

## Conclusiones
Anduvo. 3 - 7 = -4 representado como `0xFFFFFFFC`.

---

# Caso 3
## Descripción
`AND` — AND bit a bit.

## Precondiciones
- `$t1` = `0x0000FF0F`
- `$t2` = `0x00FF00FF`

## Code
```asm
AND $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x0000000F`

## Conclusiones
Anduvo. Solo quedaron en 1 los bits comunes a ambos operandos.

---

# Caso 4
## Descripción
`OR` — OR bit a bit.

## Precondiciones
- `$t1` = `0xA0A0A0A0`
- `$t2` = `0x0F0F0F0F`

## Code
```asm
OR $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0xAFAFAFAF`

## Conclusiones
Anduvo. La unión de bits produjo `0xAFAFAFAF`.

---

# Caso 5
## Descripción
`XOR` — XOR bit a bit.

## Precondiciones
- `$t1` = `0xDEADBEEF`
- `$t2` = `0xFFFFFFFF`

## Code
```asm
XOR $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x21524110`

## Conclusiones
Anduvo. XOR con `0xFFFFFFFF` invirtió todos los bits.

---

# Caso 6
## Descripción
`NOR` — NOR bit a bit.

## Precondiciones
- `$t1` = `0x0000FFFF`

## Code
```asm
NOR $t0, $t1, $zero
```

## Postcondiciones
- `$t0` = `0xFFFF0000`

## Conclusiones
Anduvo. NOR con `$zero` invirtió todos los bits de `$t1`.

---

# Caso 7
## Descripción
`SLT` — pone 1 en `$t0` si `$t1 < $t2` (con signo), 0 si no.

## Precondiciones
- `$t1` = `0x00000003`
- `$t2` = `0x00000007`

## Code
```asm
SLT $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000001`

## Conclusiones
Anduvo. 3 < 7 dio 1 en `$t0`.

---

# Caso 8
## Descripción
`SLTU` — comparación sin signo. Verifica diferencia con `SLT`.

## Precondiciones
- `$t1` = `0xFFFFFFFF`
- `$t2` = `0x00000001`

## Code
```asm
SLTU $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000000`

## Conclusiones
Anduvo. `0xFFFFFFFF` (4294967295) no es menor que 1 sin signo; con `SLT` daría 1 porque -1 < 1.

---

# Caso 9
## Descripción
`MUL` — multiplicación con signo, guarda los 32 bits bajos.

## Precondiciones
- `$t1` = `0x00000006`
- `$t2` = `0x00000007`

## Code
```asm
MUL $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x0000002A`

## Conclusiones
Anduvo. 6 × 7 = 42 = `0x2A`.

---

# Caso 10
## Descripción
`MULH` — parte alta (bits 63:32) de la multiplicación con signo.

## Precondiciones
- `$t1` = `0x00010000`
- `$t2` = `0x00010000`

## Code
```asm
MULH $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000001`

## Conclusiones
Anduvo. 65536² = `0x100000000`; MULH capturó el bit 32 del producto.

---

# Caso 11
## Descripción
`MULHU` — parte alta de la multiplicación sin signo. Verifica diferencia con `MULH`.

## Precondiciones
- `$t1` = `0xFFFFFFFF`
- `$t2` = `0x00000002`

## Code
```asm
MULHU $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000001`

## Conclusiones
Anduvo. `0xFFFFFFFF × 2 = 0x1FFFFFFFE`; parte alta = 1. Con `MULH` (con signo) daría `0xFFFFFFFF`.

---

# Caso 12
## Descripción
`DIV` — división entera con signo, guarda el cociente.

## Precondiciones
- `$t1` = `0x00000014` (20)
- `$t2` = `0x00000004` (4)

## Code
```asm
DIV $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000005`

## Conclusiones
Anduvo. 20 ÷ 4 = 5.

---

# Caso 13
## Descripción
`DIVU` — división sin signo. Verifica diferencia con `DIV`.

## Precondiciones
- `$t1` = `0xFFFFFFFE`
- `$t2` = `0x00000002`

## Code
```asm
DIVU $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x7FFFFFFF`

## Conclusiones
Anduvo. `0xFFFFFFFE ÷ 2 = 0x7FFFFFFF` sin signo. Con `DIV` daría `0xFFFFFFFF` (-1), porque -2 ÷ 2 = -1.

---

# Caso 14
## Descripción
`REST` — resto de la división entera.

## Precondiciones
- `$t1` = `0x00000011` (17)
- `$t2` = `0x00000005` (5)

## Code
```asm
REST $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x00000002`

## Conclusiones
Anduvo. 17 mod 5 = 2.

---

# Caso 15
## Descripción
`RESTU` — resto sin signo. Verifica diferencia con `REST`.

## Precondiciones
- `$t1` = `0xFFFFFFFF`
- `$t2` = `0x00000010` (16)

## Code
```asm
RESTU $t0, $t1, $t2
```

## Postcondiciones
- `$t0` = `0x0000000F`

## Conclusiones
Anduvo. `0xFFFFFFFF mod 16 = 15` sin signo.

---

# Caso 16
## Descripción
`SLL` — desplazamiento lógico izquierdo con shamt fijo.

## Precondiciones
- `$t1` = `0x00000001`

## Code
```asm
SLL $t0, $t1, 3
```

## Postcondiciones
- `$t0` = `0x00000008`

## Conclusiones
Anduvo. 1 << 3 = 8.

---

# Caso 17
## Descripción
`SRL` — desplazamiento lógico derecho (entran ceros, no preserva signo).

## Precondiciones
- `$t1` = `0x80000000`

## Code
```asm
SRL $t0, $t1, 1
```

## Postcondiciones
- `$t0` = `0x40000000`

## Conclusiones
Anduvo. El MSB se desplazó y entró un 0, confirmando desplazamiento lógico.

---

# Caso 18
## Descripción
`SRA` — desplazamiento aritmético derecho (preserva signo).

> **Discrepancia con el manual:** el manual indica `R[rs]` como fuente, pero el hardware usa `R[rt]`. El valor debe estar en `$t1` (rt=r11).

## Precondiciones
- `$t1` = `0x80000000`

## Code
Machine code: `0x0016A102`
```
[31:27]=00000 R | [26:22]=00000 rs=r0 | [21:17]=01011 rt=$t1 | [16:12]=01010 rd=$t0 | [11:7]=00010 shamt=2 | [5:0]=000010 SRA
```

## Postcondiciones
- `$t0` = `0xE0000000`

## Conclusiones
Anduvo. SRA propagó el bit de signo correctamente. El manual dice `R[rs]` pero el hardware usa `R[rt]`; con el valor en rs el resultado fue 0, con el valor en rt dio `0xE0000000`.

---

# Caso 19
## Descripción
`SLLR` — desplazamiento lógico izquierdo con cantidad variable en registro.

## Precondiciones
- `$t1` = `0x00000004` (cantidad de shift)
- `$t2` = `0x00000001` (valor a desplazar)

## Code
Encoding: `0x02D8A003`

## Postcondiciones
- `$t0` = `0x00000010`

## Conclusiones
Anduvo. 1 << 4 = 16.

---

# Caso 20
## Descripción
`SRLR` — desplazamiento lógico derecho con cantidad variable en registro.

## Precondiciones
- `$t1` = `0x00000001` (cantidad de shift)
- `$t2` = `0x80000000` (valor a desplazar)

## Code
Encoding: `0x02D8A004`

## Postcondiciones
- `$t0` = `0x40000000`

## Conclusiones
Anduvo. `0x80000000 >> 1 = 0x40000000` con cero entrante.

---

# Caso 21
## Descripción
`SRAR` — desplazamiento aritmético derecho con cantidad variable en registro.

## Precondiciones
- `$t1` = `0x00000002` (cantidad de shift)
- `$t2` = `0x80000000` (valor a desplazar)

## Code
Encoding: `0x02D8A005`

## Postcondiciones
- `$t0` = `0xE0000000`

## Conclusiones
Anduvo. `0x80000000 >>> 2 = 0xE0000000`; el bit de signo se propagó.

---

# Caso 22
## Descripción
`ADDI` — suma con inmediato de 17 bits con signo.

## Precondiciones
- `$t1` = `0x00000000`

## Code
```asm
ADDI $t0, $t1, 42
```

## Postcondiciones
- `$t0` = `0x0000002A`

## Conclusiones
Anduvo. 0 + 42 = 42.

---

# Caso 23
## Descripción
`LUI` — carga inmediato en los 16 bits altos del registro.

## Precondiciones
_(ninguna)_

## Code
Encoding: `0x3814BEEF`

## Postcondiciones
- `$t0` = `0xBEEF0000`

## Conclusiones
Anduvo. `0xBEEF` quedó en los 16 bits altos y los bajos en cero.

---

# Caso 24
## Descripción
`ANDI` — AND con inmediato de 16 bits (zero-extended).

## Precondiciones
- `$t1` = `0xDEADBEEF`

## Code
```asm
ANDI $t0, $t1, 0x00FF
```

## Postcondiciones
- `$t0` = `0x000000EF`

## Conclusiones
Anduvo. `0xDEADBEEF & 0x00FF = 0xEF`.

---

# Caso 25
## Descripción
`ORI` — OR con inmediato de 16 bits (zero-extended).

## Precondiciones
- `$t1` = `0xDEAD0000`

## Code
```asm
ORI $t0, $t1, 0xBEEF
```

## Postcondiciones
- `$t0` = `0xDEADBEEF`

## Conclusiones
Anduvo. OR combinó la parte alta con el inmediato bajo.

---

# Caso 26
## Descripción
`XORI` — XOR con inmediato de 16 bits (zero-extended).

## Precondiciones
- `$t1` = `0xABCDFFFF`

## Code
```asm
XORI $t0, $t1, 0xFFFF
```

## Postcondiciones
- `$t0` = `0xABCD0000`

## Conclusiones
Anduvo. XOR de los 16 bits bajos con `0xFFFF` los puso todos en 0.

---

# Caso 27
## Descripción
`SLTI` — comparación con inmediato con signo.

## Precondiciones
- `$t1` = `0x00000000`

## Code
```asm
SLTI $t0, $t1, 100
```

## Postcondiciones
- `$t0` = `0x00000001`

## Conclusiones
Anduvo. 0 < 100 dio 1.

---

# Caso 28
## Descripción
`SLTIU` — comparación con inmediato sin signo. Verifica diferencia con `SLTI`.

## Precondiciones
- `$t1` = `0xFFFFFFFF`

## Code
```asm
SLTIU $t0, $t1, 100
```

## Postcondiciones
- `$t0` = `0x00000000`

## Conclusiones
Anduvo. `0xFFFFFFFF` (4294967295) no es menor que 100 sin signo; con `SLTI` daría 1 porque -1 < 100.

---

# Caso 29
## Descripción
`SW` / `LW` — guardar y cargar una palabra de 32 bits con offset 0.

## Precondiciones
- `$t0` = `0xCAFE1234`
- `$t1` = `0x00000010`

## Code
SW encoding: `0x4AD40000` | LW encoding: `0x42D40000`

## Postcondiciones
- `$t0` = `0xCAFE1234` (después del LW)

## Conclusiones
Anduvo. SW guardó en `0x00000010` y LW lo recuperó sin alteraciones.

---

# Caso 30
## Descripción
`SW` / `LW` con offset — verifica EA = R[rs] + imm.

## Precondiciones
- `$t0` = `0xABCD0000`
- `$t1` = `0x00000010`

## Code
SW encoding: `0x4AD40004` | LW encoding: `0x42D40004`

## Postcondiciones
- `$t0` = `0xABCD0000` (leído desde `0x00000014`)

## Conclusiones
Anduvo. El offset 4 se sumó a la base sin pisar el dato del Caso 29.

---

# Caso 31
## Descripción
`SB` / `LB` — guardar y cargar un byte con extensión de signo.

## Precondiciones
- `$t0` = `0x000000FF`
- `$t1` = `0x00000010`

## Code
SB encoding: `0x5AD40000` | LB encoding: `0x72D40000`

## Postcondiciones
- `$t0` = `0xFFFFFFFF`

## Conclusiones
Anduvo. SB guardó el byte bajo y LB lo recuperó extendiendo el signo (`0xFF` → `0xFFFFFFFF`).

---

# Caso 32
## Descripción
`LBU` — cargar byte sin extensión de signo. Verifica diferencia con `LB`.

## Precondiciones
- Byte `0xFF` en `0x00000010` (del Caso 31)
- `$t1` = `0x00000010`

## Code
Encoding: `0x7AD40000`

## Postcondiciones
- `$t0` = `0x000000FF`

## Conclusiones
Anduvo. El mismo `0xFF` resultó en 255 en lugar de -1 al no extenderse el signo.

---

# Caso 33
## Descripción
`SH` / `LH` — guardar y cargar una media palabra con extensión de signo.

## Precondiciones
- `$t0` = `0x0000FFFF`
- `$t1` = `0x00000010`

## Code
SH encoding: `0x52D40000` | LH encoding: `0x62D40000`

## Postcondiciones
- `$t0` = `0xFFFFFFFF`

## Conclusiones
Anduvo. SH guardó `0xFFFF` y LH lo recuperó extendiendo el signo.

---

# Caso 34
## Descripción
`LHU` — cargar media palabra sin extensión de signo. Verifica diferencia con `LH`.

## Precondiciones
- `M[0x10][15:0]` = `0xFFFF` (del Caso 33)
- `$t1` = `0x00000010`

## Code
Encoding: `0x6AD40000`

## Postcondiciones
- `$t0` = `0x0000FFFF`

## Conclusiones
Anduvo. `0xFFFF` con extensión de ceros = `0x0000FFFF`; con `LH` daría `0xFFFFFFFF`.

---

# Caso 35
## Descripción
`BEQ` — salta si rs == rt.

## Precondiciones
- `$t1` = `$t2` = `0x00000010`

## Code
Encoding: `0x82D80001`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. La rama se tomó: PC = 0 + 4 + (1 × 4) = 8.

---

# Caso 36
## Descripción
`BNE` — salta si rs ≠ rt.

## Precondiciones
- `$t1` = `0x00000001`
- `$t2` = `0x00000002`

## Code
Encoding: `0x8AD80001`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. La rama se tomó porque `$t1 ≠ $t2`.

---

# Caso 37
## Descripción
`BLT` — salta si rs < rt (comparación con signo).

## Precondiciones
- `$t1` = `0xFFFFFFFF` (-1)
- `$t2` = `0x00000001`

## Code
Encoding: `0x92D80001`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. `0xFFFFFFFF` se trató como -1 (signed), -1 < 1 tomó la rama.

---

# Caso 38
## Descripción
`BGT` — salta si rs > rt (comparación con signo).

## Precondiciones
- `$t1` = `0x0000000A` (10)
- `$t2` = `0x00000001` (1)

## Code
Encoding: `0x9AD80001`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. 10 > 1 tomó la rama.

---

# Caso 39
## Descripción
`BLE` — salta si rs ≤ rt (comparación con signo).

## Precondiciones
- `$t1` = `0x00000001`
- `$t2` = `0x0000000A` (10)

## Code
Encoding: `0xA2D80001`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. 1 ≤ 10 tomó la rama.

---

# Caso 40
## Descripción
`BGE` — salta si rs ≥ rt (comparación con signo). Caso con igualdad.

## Precondiciones
- `$t1` = `0x0000000A`
- `$t2` = `0x0000000A`

## Code
Encoding: `0xAAD80001`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. 10 ≥ 10 (igualdad) tomó la rama.

---

# Caso 41
## Descripción
`J` — salto incondicional J-type.

## Precondiciones
_(ninguna)_

## Code
Encoding: `0x10000002`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. `{PC+4[31:29], 2, 2'b0}` = `0x00000008`.

---

# Caso 42
## Descripción
`JAL` — salto con link; guarda la dirección de retorno en `$ra`.

## Precondiciones
_(ninguna)_

## Code
Encoding: `0x18000002`

## Postcondiciones
- PC = `0x00000008`
- `$ra` = `0x00000004`

## Conclusiones
Anduvo. PC saltó a 8 y `$ra` = PC+4 = 4 para el retorno.

---

# Caso 43
## Descripción
`JR` — salto a dirección contenida en registro.

## Precondiciones
- `$t1` = `0x00000008`

## Code
Encoding: `0x02C0000E`

## Postcondiciones
- PC = `0x00000008`

## Conclusiones
Anduvo. PC tomó el valor de `$t1`.

---

# Caso 44
## Descripción
`JALR` — salto a registro con link.

## Precondiciones
- `$t1` = `0x00000008`

## Code
Encoding: `0x02C0000F`

## Postcondiciones
- PC = `0x00000008`
- `$ra` = `0x00000004`

## Conclusiones
Anduvo. Saltó a `$t1` y guardó PC+4 en `$ra`.

---

# Caso 45
## Descripción
`LWX` — carga de palabra indexada: EA = R[rs] + R[rd].

## Precondiciones
- `$t1` = `0x00000010` (base)
- `$zero` = `0x00000000` (índice)
- `M[0x10]` = `0xCAFE1234` (cargado con SW previo)

## Code
Encoding: `0x02D40014`

## Postcondiciones
- `$t0` = `0xCAFE1234`

## Conclusiones
Anduvo. Cargó la palabra en `M[$t1 + $zero]` = `M[0x10]`.

---

# Caso 46
## Descripción
`LHX` — carga de media palabra indexada con signo: EA = R[rs] + R[rd].

## Precondiciones
- `$t1` = `0x00000010` (base)
- `$zero` = `0x00000000` (índice)
- `M[0x10]` = `0xCAFE1234`

## Code
Encoding: `0x02D40010`

## Postcondiciones
- `$t0` = `0x00001234`

## Conclusiones
Anduvo. `M[0x10][15:0] = 0x1234`; extensión de signo no cambia el valor porque el MSB es 0.

---

# Caso 47
## Descripción
`LHUX` — carga de media palabra indexada sin signo. Verifica diferencia con `LHX`.

## Precondiciones
- `$t1` = `0x00000010` (base)
- `$zero` = `0x00000000` (índice)
- `M[0x10]` = `0xCAFE1234`

## Code
Encoding: `0x02D40011`

## Postcondiciones
- `$t0` = `0x00001234`

## Conclusiones
Anduvo. Mismo resultado que `LHX` porque `M[0x10][15:0] = 0x1234` tiene MSB = 0; la diferencia se observaría con un halfword negativo.

---

# Caso 48
## Descripción
`LBX` — carga de byte indexado con signo: EA = R[rs] + R[rd].

## Precondiciones
- `$t1` = `0x00000010` (base)
- `$zero` = `0x00000000` (índice)
- `M[0x10][7:0]` = `0xFF` (cargado con SB previo)

## Code
Encoding: `0x02D40012`

## Postcondiciones
- `$t0` = `0xFFFFFFFF`

## Conclusiones
Anduvo. `0xFF` con extensión de signo = `0xFFFFFFFF`.

---

# Caso 49
## Descripción
`LBUX` — carga de byte indexado sin signo. Verifica diferencia con `LBX`.

## Precondiciones
- `$t1` = `0x00000010` (base)
- `$zero` = `0x00000000` (índice)
- `M[0x10][7:0]` = `0xFF` (cargado con SB previo)

## Code
Encoding: `0x02D40013`

## Postcondiciones
- `$t0` = `0x000000FF`

## Conclusiones
Anduvo. `0xFF` sin extensión de signo = 255.

---

# Caso 50
## Descripción
`ANDIH` — AND con inmediato en los 16 bits altos (h=1): R[rt] = R[rs] & (ims << 16).

## Precondiciones
- `$t1` = `0xFFFFFFFF`

## Code
Encoding: `0x22D51234`

## Postcondiciones
- `$t0` = `0x12340000`

## Conclusiones
Anduvo. `0xFFFFFFFF & 0x12340000 = 0x12340000`.

---

# Caso 51
## Descripción
`ORIH` — OR con inmediato en los 16 bits altos (h=1): R[rt] = R[rs] | (ims << 16).

## Precondiciones
- `$t1` = `0x00000000`

## Code
Encoding: `0x2AD5BEEF`

## Postcondiciones
- `$t0` = `0xBEEF0000`

## Conclusiones
Anduvo. `0x00000000 | 0xBEEF0000 = 0xBEEF0000`.

---

# Caso 52
## Descripción
`XORIH` — XOR con inmediato en los 16 bits altos (h=1): R[rt] = R[rs] ^ (ims << 16).

## Precondiciones
- `$t1` = `0xBEEF0000`

## Code
Encoding: `0x32D5BEEF`

## Postcondiciones
- `$t0` = `0x00000000`

## Conclusiones
Anduvo. `0xBEEF0000 ^ 0xBEEF0000 = 0x00000000`.

---

# Caso 53
## Descripción
`CFS` / `CTS` — leer y escribir registros especiales del sistema (PSW, ECR, EPC, BVA, VBR).

## Conclusiones
No se pueden testear en el simulador: requieren el sistema de registros especiales inicializado, que no está disponible en el entorno de debug.

---

# Caso 54
## Descripción
`TRAP` / `RFT` — generar excepción de software y retornar de ella.

## Conclusiones
No se pueden testear en el simulador: requieren tabla de vectores de excepción configurada en VBR y memoria de manejo de interrupciones inicializada.
