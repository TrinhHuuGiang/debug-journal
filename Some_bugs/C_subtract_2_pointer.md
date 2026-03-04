#### POINTER SUBTRACTION TRONG C

Với:
A *p1;
A *p2;

Nếu p1 và p2 cùng một mảng:

p2 - p1 = số phần tử kiểu A giữa chúng (kiểu trả về: ptrdiff_t)
Không phải số byte.

Bên trong tương đương:
(byte_diff) / sizeof(A)

Nếu khác mảng (con trỏ khác nhau) → Undefined Behavior.

Muốn tính khoảng cách địa chỉ theo byte:
(char*)p2 - (char*)p1
