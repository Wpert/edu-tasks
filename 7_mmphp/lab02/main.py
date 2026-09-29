import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# ------------------- Параметры модели -------------------
l = 0.001          # время жизни мгновенных нейтронов, с
beta = 0.0065      # доля запаздывающих нейтронов
lambda_ = 0.0765   # постоянная распада предшественников, 1/с
n_ust = 0.5        # целевая относительная мощность (n_уст)
alpha_w = -0.017   # коэффициент реактивности по мощности (α_w)
tau_p = 0.01       # постоянная времени системы регулирования, с
x0 = 100           # коэффициент усиления системы регулирования

# Начальные условия
dw0 = (1 - n_ust) / n_ust  # δw(0)
dc0 = (1 - n_ust) / n_ust  # δc(0)
rho0 = 0.0
Z0 = 0.0
y0 = np.array([dw0, dc0, rho0, Z0])

# Время интегрирования
t_start = 0.0
t_end = 2.0
h = 0.005
t_values = np.arange(t_start, t_end + h, h)

# ------------------- Правая часть системы -------------------
def deriv(t, y, A, B):
    """
    y = [δw, δc, ρ_cm, Z]
    A, B — ключи включения обратных связей.
    """
    dw, dc, rho, Z = y
    ddw = (A * rho + (B * alpha_w * n_ust - beta) * dw) / l + (beta / l) * dc
    ddc = lambda_ * (dw - dc)
    drho = Z
    dZ = -Z / tau_p - (x0 / tau_p) * dw
    return np.array([ddw, ddc, drho, dZ])

# ------------------- Метод Рунге–Кутты 4-го порядка -------------------
def rk4_step(t, y, h, A, B):
    k1 = h * deriv(t, y, A, B)
    k2 = h * deriv(t + h/2, y + k1/2, A, B)
    k3 = h * deriv(t + h/2, y + k2/2, A, B)
    k4 = h * deriv(t + h, y + k3, A, B)
    return y + (k1 + 2*k2 + 2*k3 + k4) / 6

def simulate(A, B, t_values, y0, h):
    n_steps = len(t_values)
    y = np.zeros((n_steps, 4))
    y[0] = y0
    for i in range(1, n_steps):
        y[i] = rk4_step(t_values[i-1], y[i-1], h, A, B)
    return y

# ------------------- Расчёт для разных режимов -------------------
cases = [
    (1, 1, "A=1, B=1 (обе обратные связи)"),
    (0, 1, "A=0, B=1 (только по мощности)"),
    (1, 0, "A=1, B=0 (только регулятор)"),
    (0, 0, "A=0, B=0 (без обратных связей)")
]

results = {}
for A, B, label in cases:
    y = simulate(A, B, t_values, y0, h)
    results[label] = y
    print(f"Расчёт для {label} завершён.")

# ------------------- Сохранение в Excel -------------------
with pd.ExcelWriter('lab_results.xlsx') as writer:
    for label, y in results.items():
        df = pd.DataFrame({
            't': t_values,
            'dw': y[:, 0],
            'dc': y[:, 1],
            'rho_cm': y[:, 2],
            'Z': y[:, 3]
        })
        sheet_name = label.replace('=', '').replace(',', '').replace(' ', '_')[:31]
        df.to_excel(writer, sheet_name=sheet_name, index=False)
print("Данные сохранены в lab_results.xlsx")

# ------------------- Построение графиков -------------------
plt.figure(figsize=(12, 8))

# δw
plt.subplot(2, 2, 1)
for label, y in results.items():
    plt.plot(t_values, y[:, 0], label=label)
plt.xlabel('Время, с')
plt.ylabel('δw')
plt.title('Отклонение мощности')
plt.legend()
plt.grid(True)

# ρ_cm
plt.subplot(2, 2, 2)
for label, y in results.items():
    plt.plot(t_values, y[:, 2], label=label)
plt.xlabel('Время, с')
plt.ylabel('ρ_cm')
plt.title('Реактивность регулятора')
plt.legend()
plt.grid(True)

# Z
plt.subplot(2, 2, 3)
for label, y in results.items():
    plt.plot(t_values, y[:, 3], label=label)
plt.xlabel('Время, с')
plt.ylabel('Z')
plt.title('Скорость изменения ρ_cm')
plt.legend()
plt.grid(True)

# δc
plt.subplot(2, 2, 4)
for label, y in results.items():
    plt.plot(t_values, y[:, 1], label=label)
plt.xlabel('Время, с')
plt.ylabel('δc')
plt.title('Концентрация запаздывающих нейтронов')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig('lab_plots.png', dpi=300)
plt.show()
