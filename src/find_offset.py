#!/usr/bin/env python3
from pwn import cyclic_find

# Der überschriebenen Rücksprungzeiger aus GDB (als Integer)
# Hinweis: Achte auf die korrekte Umrechnung von little endian!
# Für pwntools kannst du den Wert direkt angeben. Oft liefert das Tool
# den korrekten Offset, wenn du z. B. 0x616161706161616f verwendest.
offset = cyclic_find(0x616161706161616f)
print("Offset:", offset)
