import sys
import random

def generate_matrix_file(filename, n, mode='random'):
    """
    Генерирует файл с матрицей размера n x n.
    mode: 'random' - случайные числа, 'identity' - единичная матрица (для проверки)
    """
    with open(filename, 'w') as f:
        for i in range(n):
            row = []
            for j in range(n):
                if mode == 'identity':
                    val = 1.0 if i == j else 0.0
                else:
                    val = random.uniform(-10.0, 10.0)
                row.append(f"{val:.6f}")            
            f.write(" ".join(row) + "\n")
    
    print(f"Файл {filename} успешно создан (размер {n}x{n}).")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Использование: python generate_data.py <n> <output_prefix>")
        print("Пример: python generate_data.py 1000 data")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
        prefix = sys.argv[2]
        
        if n <= 0:
            raise ValueError("Размер матрицы должен быть положительным")

        generate_matrix_file(f"{prefix}_A.txt", n, mode='random')
        generate_matrix_file(f"{prefix}_B.txt", n, mode='random')
        
    except ValueError as e:
        print(f"Ошибка: {e}")
        sys.exit(1)
