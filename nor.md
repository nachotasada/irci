Compuerta NOR de 16 bits con Registro
¿Qué hace este circuito?
Toma dos datos de 16 bits, les aplica la operación lógica NOR invirtiendo los resultados de un OR y guarda ese resultado final en una memoria.

¿Para qué sirve en un procesador real?
Detectar ceros: Se usa un NOR para revisar si todos los bits de un resultado son cero. Esto le sirve al procesador para tomar decisiones.
Es universal: Puede combinarse con otras para crear cualquier otro tipo de compuerta lógica

Diseño en CircuitVerse
Buses de datos: Configuré las entradas y la compuerta a 16 bits (Bit Width: 16). Así toda la información viaja agrupada por un solo cable.
Registro: Utilicé un D Flip-Flop configurado a 16 bits para almacenar la palabra de datos completa.
Control por Reloj: Le conecté un Clock al Flip-Flop que hace que el resultado de la operación se guarde en la memoria.
