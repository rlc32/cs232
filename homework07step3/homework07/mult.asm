# Multiply two numbers, found in locations 10 and 11, leaving the result in location 12.
# Assumes this code is loaded at location 20.
__main: 20
mov 0 34
mov *32 reg2
jez reg2 31
mov *33 reg1
jez reg1 31
mov reg2 reg0
sub 1 reg1
jez reg1 30
add reg0 reg2
jmp 26
mov reg2 34
end
__data: 3
