RAM_SIZE = 1024


class RAM:
    def __init__(self, size=RAM_SIZE):
        self._minAddr = 0
        self._maxAddr = RAM_SIZE - 1
        self._memory = []   # a list of values.  Could be #s or instructions.
        for i in range(size):
            self._memory.append(0)

    def __getitem__(self, addr):
        return self._memory[addr]

    def __setitem__(self, addr, val):
        self._memory[addr] = val

    def is_legal_addr(self, addr):
        return self._minAddr <= addr <= self._maxAddr

class MMU:
    def __init__(self, ramObj):
        self._ram = ramObj
        self._reloc = 0
        self._limit = 0
    def getitem(self, addr):
        physical = addr + self._reloc
        if addr < 0:
            print('BAD ADDRESS %d: TOO LOW' % (addr))
        elif physical > self._limit:
            print('BAD ADDRESS %d: TOO HIGH' % (addr))
        else:
            return self._ram[physical]

    def setitem(self, addr, val):
        physical = addr + self._reloc
        if addr < 0:
            print('BAD ADDRESS %d: TOO LOW' % (addr))
        elif physical > self._limit:
            print('BAD ADDRESS %d: TOO HIGH' % (addr))
        else:
            self._ram[physical] = val

    def set_reloc(self, low):
        self._reloc = low
    def set_limit(self, high):
        self._limit = high
