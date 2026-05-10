# CẨM NANG TỔ HỢP CHO LẬP TRÌNH VIÊN & TOÁN HỌC (v2)

Tài liệu này tổng hợp các quy tắc, công thức rút gọn và mẹo ước lượng nhanh để giải quyết các bài toán đếm, đặc biệt hữu ích trong Competitive Programming và phân tích thuật toán.

---

## 1. CÁC CÔNG THỨC CƠ BẢN & BIẾN THỂ

### 1.1. Tổ hợp chập k của n (Không lặp, không thứ tự)
- **Công thức:**
$$C_n^k = \frac{n!}{k!(n-k)!}$$
- **Tính chất đối xứng:** $C_n^k = C_n^{n-k}$
- **Ý nghĩa:** Chọn tập con $k$ phần tử từ tập $n$ phần tử.

### 1.2. Tổ hợp lặp (Không thứ tự, có lặp)
- **Công thức:**
$$H_n^d = C_{n+d-1}^d = C_{n+d-1}^{n-1}$$
- **Mô hình "Vách ngăn":** Chọn $d$ vật từ $n$ loại tương đương việc xếp $d$ ngôi sao và $n-1$ vách ngăn.
- **Bài toán nghiệm nguyên:** Số nghiệm nguyên không âm của $x_1 + x_2 + ... + x_n = d$ là $C_{n+d-1}^{n-1}$.

### 1.3. Chỉnh hợp lặp (Có thứ tự, có lặp)
- **Công thức:** $n^d$
- **Ý nghĩa:** Mỗi vị trí có $n$ cách chọn độc lập (Mật khẩu, dãy bit...).

---

## 2. CÁC ĐẲNG THỨC RÚT GỌN QUAN TRỌNG

### 2.1. Đẳng thức Pascal (Dùng cho Quy hoạch động)
$$C_n^k = C_{n-1}^k + C_{n-1}^{k-1}$$
- Ứng dụng xây dựng Tam giác Pascal với độ phức tạp $O(n^2)$.

### 2.2. Tổng các tổ hợp (Tập lũy thừa)
$$\sum_{k=0}^{n} C_n^k = 2^n$$
- Ý nghĩa: Tổng số tập con của một tập hợp có $n$ phần tử.

### 2.3. Đẳng thức Hockey-stick (Gậy khúc côn cầu)
$$\sum_{i=k}^{n} C_i^k = C_{n+1}^{k+1}$$
- Dùng để rút gọn các tổng có chỉ số dưới tăng dần, chỉ số trên cố định.
- **Lưu ý:** Tổng phải bắt đầu từ $i=k$.

---

## 3. MẸO ƯỚC LƯỢNG NHANH (Complexity Estimation)

### 3.1. Quy tắc "Mũ và Căn" (Cho k xấp xỉ n/2)
$$C_n^{n/2} \approx \frac{2^n}{\sqrt{n}}$$
- **Dùng để check TLE:** - $n=20 \implies \approx 1.8 \times 10^5$ (An toàn)
  - $n=30 \implies \approx 1.5 \times 10^8$ (Nguy hiểm cho giới hạn 1s)

### 3.2. Ước lượng Đa thức (Cho k nhỏ)
$$C_n^k \approx \frac{n^k}{k!}$$
- Ví dụ: $C_n^2 \approx \frac{n^2}{2}$, $C_n^3 \approx \frac{n^3}{6}$.

### 3.3. Ước lượng Bậc lũy thừa thực dụng
$$C_n^k \approx \left( \frac{n \cdot 2}{k} \right)^k$$
- Giúp xác định nhanh số lượng chữ số (order of magnitude).

---

## 4. CHÚ Ý KHI LẬP TRÌNH (Competitive Programming)

### 4.1. Tràn số (Overflow)
- $C_{30}^{15} \approx 1.5 \times 10^8$ (Vừa đủ `int` 32-bit).
- $C_{60}^{30} \approx 1.1 \times 10^{17}$ (Sắp tràn `long long` 64-bit).
- **Giải pháp:** Sử dụng Nghịch đảo nhân Modulo nếu đề yêu cầu chia dư.

### 4.2. Độ phức tạp (Time Complexity)
- **Tính trực tiếp:** $O(k)$ (Dễ tràn số trung gian).
- **Quy hoạch động (Pascal):** $O(n^2)$ (An toàn cho $n \le 5000$).
- **Giai thừa + Modulo Inverse:** $O(n)$ tiền xử lý, $O(1)$ mỗi truy vấn.

### 4.3. Phân biệt Thứ tự
- **Thứ tự quan trọng:** Kết quả $(1,2) \neq (2,1)$. Dùng $n^k$ hoặc $A_n^k$.
- **Thứ tự KHÔNG quan trọng:** Kết quả $(1,2) = (2,1)$. Dùng $C_n^k$ hoặc $H_n^k$.