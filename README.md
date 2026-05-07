# CHIẾN THUẬT GIẢI QUYẾT BÀI TOÁN CP KHI CHƯA BIẾT BẮT ĐẦU TỪ ĐÂU

Cảm giác bế tắc trước một bài toán Competitive Programming (CP) là điều bình thường. Quy trình 6 bước dưới đây sẽ giúp bạn phá vỡ sự bế tắc và tìm ra hướng đi đúng đắn.

---

## 1. Phân tích Giới hạn (Constraints Analysis) - "Kim chỉ nam"
Giới hạn dữ liệu cho bạn biết độ phức tạp thời gian cho phép. Hãy nhìn vào giá trị lớn nhất ($N$):

| Giới hạn $N$ | Độ phức tạp tối đa | Thuật toán gợi ý |
| :--- | :--- | :--- |
| $N \le 10 \dots 12$ | $O(N!)$ hoặc $O(2^N \cdot N^2)$ | Quay lui (Backtracking), Hoán vị |
| $N \le 20 \dots 25$ | $O(2^N \cdot N)$ | Quy hoạch động trạng thái (Bitmask DP) |
| $N \le 500$ | $O(N^3)$ | Floyd-Warshall, DP 3 lớp |
| $N \le 5000$ | $O(N^2)$ | DP, Duyệt hai vòng lặp, Đồ thị cơ bản |
| $N \le 10^5 \dots 10^6$ | $O(N \log N)$ hoặc $O(N)$ | Sắp xếp, Chặt nhị phân, Segment Tree, Fenwick Tree |
| $N > 10^8$ | $O(\log N)$ hoặc $O(1)$ | Toán học, Nhân ma trận, Lý thuyết số |



---

## 2. Giải tay và Quan sát quy luật (Manual Simulation)
Đây là bước quan trọng nhất để hiểu bản chất bài toán.
- **Thử Test Case nhỏ:** Tự tạo các bộ dữ liệu với $N=3, 4, 5$.
- **Trường hợp biên (Edge Cases):**
    - Mảng rỗng hoặc chỉ có 1 phần tử.
    - Các phần tử giống hệt nhau.
    - Đồ thị không liên thông hoặc có chu trình.
    - Số cực đại, số cực tiểu, số âm.
- **Vẽ hình:** Nếu là bài toán đồ thị hoặc hình học, hãy vẽ ra giấy. Sự kết nối trực quan thường gợi mở ý tưởng tốt hơn suy nghĩ thuần túy.

---

## 3. Đơn giản hóa đề bài (Problem Reduction)
Nếu chưa giải được bài toán gốc, hãy giải phiên bản "dễ hơn" của nó:
- **Giảm chiều:** Thay vì mảng 2 chiều, hãy thử giải trên mảng 1 chiều.
- **Thêm điều kiện:** "Nếu mảng đã được sắp xếp thì sao?", "Nếu đồ thị là một cái Cây (Tree) thì sao?".
- **Bỏ bớt điều kiện:** Giải bài toán khi không có các ràng buộc phụ để tìm ra cấu trúc cốt lõi.

---

## 4. Thay đổi góc nhìn (Reverse & Lateral Thinking)
Khi đi đường thẳng không được, hãy thử đi đường vòng:
- **Chặt nhị phân đáp án:** Nếu đề bài có dạng "Tìm giá trị $X$ nhỏ nhất/lớn nhất để thỏa mãn...", hãy thử kiểm tra xem một giá trị $X$ bất kỳ có thỏa mãn hay không.
- **Tính phần bù (Complementary Counting):** Thay vì đếm số cách *thỏa mãn*, hãy lấy *tổng số cách* trừ đi *số cách không thỏa mãn*.
- **Làm ngược (Reverse Thinking):** Đi từ kết quả cuối cùng ngược về trạng thái ban đầu. Điều này cực kỳ hiệu quả trong các bài toán đồ thị hoặc DP.

---

## 5. Áp dụng các "Mẫu hình" phổ biến (Pattern Matching)
Duyệt nhanh danh sách các kỹ thuật này trong đầu:
1.  **Greedy (Tham lam):** Có thể chọn cái tốt nhất hiện tại mà không hối hận không? (Thường đi kèm với Sắp xếp).
2.  **Dynamic Programming (DP):** Kết quả hiện tại có dựa trên các bài toán con nhỏ hơn đã giải không?
3.  **Two Pointers / Sliding Window:** Thường dùng cho các bài toán trên mảng liên tục.
4.  **Đồ thị (BFS/DFS/Dijkstra):** Có thể mô hình hóa các trạng thái thành các nút và sự biến đổi thành các cạnh không?

---

## 6. Kỹ thuật "Cứu cánh" khi bế tắc hoàn toàn
- **Rubber Duck Debugging:** Thử giải thích đề bài cho một người bạn (hoặc một đồ vật). Khi phải phát ngôn, não bộ sẽ tổ chức lại thông tin logic hơn.
- **Viết trình "Chạy trâu" (Brute-force):** Nếu không nghĩ ra thuật tối ưu, hãy code cách chạy trâu để lấy một phần số điểm (Subtask) và dùng nó để so sánh kết quả khi tìm ra thuật mới.
- **Tạm rời mắt:** Đứng dậy đi uống nước hoặc đi dạo 5 phút. "Aha moment" thường đến khi bạn không quá căng thẳng.

---

## Danh sách kiểm tra (Checklist) nhanh:
- [ ] Đã đọc kỹ đề để không bỏ sót điều kiện nhỏ chưa?
- [ ] Giới hạn bộ nhớ và thời gian là bao nhiêu?
- [ ] Có thể đưa về bài toán toán học nào không (tổ hợp, ước chung, modulo)?
- [ ] Nếu bế tắc sau 30-45p: **Đọc Editorial** để học thêm kỹ thuật mới.

> **Ghi chú:** Mục tiêu của luyện tập không phải là giải mọi bài ngay lập tức, mà là tích lũy thêm "mẫu hình" để gặp lại ở những bài sau.
## 7. Dự đoán độ phức tạp với nhiều biến đầu vào ($N, M, K, Q$)

Khi bài toán có nhiều tham số, việc xác định thuật toán không chỉ dựa vào một biến duy nhất mà dựa vào **tổng khối lượng tính toán** (ngưỡng $10^8$ phép tính/giây).

### 7.1. Quy tắc tổ hợp biến phổ biến
Dựa vào các giá trị đầu vào, bạn có thể định hướng thuật toán như sau:

| Giới hạn biến | Độ phức tạp dự kiến | Hướng giải gợi ý |
| :--- | :--- | :--- |
| $N, M \le 10^5$ | $O(N + M)$ hoặc $O((N+M) \log \dots)$ | Duyệt song song, Cấu trúc dữ liệu, Two Pointers. |
| $N \cdot M \le 10^6 \dots 10^7$ | $O(N \cdot M)$ | Quy hoạch động, Duyệt lưới, Đồ thị cơ bản. |
| $N \le 10^5, K \le 20$ | $O(N \cdot 2^K)$ hoặc $O(N \cdot K)$ | DP Bitmask, Xử lý trạng thái nhỏ cho mỗi phần tử lớn. |
| $N \le 10^5, Q \le 10^5$ | $O(Q \log N)$ | Truy vấn (Queries) dùng Segment Tree, Fenwick Tree hoặc Sparse Table. |
| $V \le 10^5, E \le 2 \cdot 10^5$ | $O(E \log V)$ | Thuật toán đồ thị tối ưu (Dijkstra, Kruskal, Tarjan). |
| $N, M \le 10^9$ | $O(\sqrt{N})$ hoặc $O(\log N)$ | Chặt nhị phân, Chia căn (Square Root Decomposition), Toán học. |



### 7.2. Các dấu hiệu đặc biệt từ Input

#### A. Tổng các bộ test ($\sum N$)
Nếu đề bài ghi: *"Tổng của N qua các bộ test không quá $2 \cdot 10^5$"*:
*   **Chiến thuật:** Tập trung giải bài toán cho 1 bộ test với $O(N \log N)$ hoặc $O(N)$.
*   **Lưu ý:** Không khởi tạo lại mảng lớn bằng `memset` hoặc vòng lặp $O(N_{max})$ trong mỗi test case vì sẽ gây TLE. Chỉ xóa các phần tử thực sự sử dụng.

#### B. Biến "Siêu nhỏ" ($K \le 10 \dots 20$)
Đây thường là dấu hiệu của:
*   **Exponential Complexity:** Thuật toán có số mũ liên quan đến $K$.
*   **DP trạng thái:** Dùng bitmask để lưu trữ các tập hợp con của $K$.

#### C. Mối quan hệ giữa Đồ thị và Truy vấn
Nếu có $N$ đỉnh và $Q$ truy vấn:
*   Nếu $Q$ lớn ($10^5$): Phải dùng cấu trúc dữ liệu để trả lời mỗi truy vấn trong $O(\log N)$ hoặc $O(1)$.
*   Nếu $Q$ nhỏ ($100$): Có thể chạy thuật toán đồ thị (như BFS/Dijkstra) lại nhiều lần.

### 7.3. Kỹ thuật "Chia căn" ($\sqrt{N}$)
Khi bạn gặp các biến có tích $N \cdot M \le 10^9$ nhưng chúng có thể thay đổi độc lập:
*   Nếu $N$ nhỏ, $M$ lớn: Dùng thuật toán A.
*   Nếu $N$ lớn, $M$ nhỏ: Dùng thuật toán B.
*   Ngưỡng chia thường là $\sqrt{Limit}$.
### 7.4. Đặc thù bài toán Ma trận ($R$ hàng, $C$ cột)

Khi làm việc với lưới (Grid) hoặc ma trận, tích $R \cdot C$ chính là "biến số" quyết định.

| Giới hạn $R, C$ | Độ phức tạp | Hướng giải gợi ý |
| :--- | :--- | :--- |
| $R, C \le 10$ | $O((R \cdot C)!)$ | Quay lui, tìm đường đi dài nhất, bài toán lát gạch phức tạp. |
| $R, C \le 20$ | $O(2^{R \cdot C})$ hoặc $O(3^{R \cdot C})$ | DP Bitmask trên từng ô hoặc từng dòng. |
| $R \cdot C \le 10^6$ | $O(R \cdot C)$ | BFS/DFS tìm đường ngắn nhất, DP (di chuyển Phải/Xuống), Loang (Flood Fill). |
| $R \cdot C \le 10^6$ | $O(R \cdot C \cdot \log(\dots))$ | Dijkstra trên lưới, Cây phân đoạn 2D (2D Segment Tree). |
| $R, C \le 10^9$ | $O(K \log K)$ | Nếu chỉ có $K$ điểm đặc biệt trên lưới: Nén tọa độ (Coordinate Compression). |
| $R \le 100, C \le 10^{18}$ | $O(R^3 \log C)$ | Nhân ma trận (Matrix Exponentiation) để tăng tốc DP. |

#### Các kỹ thuật "phải biết" với Ma trận:
1.  **Mảng cộng dồn 2D (2D Prefix Sum):**
    *   Giúp tính tổng bất kỳ hình chữ nhật con nào trong $O(1)$.
    *   Công thức: `S[i][j] = A[i][j] + S[i-1][j] + S[i][j-1] - S[i-1][j-1]`.
2.  **Kỹ thuật duyệt láng giềng:**
    *   Sử dụng hai mảng hướng `dx[] = {0, 0, 1, -1}` và `dy[] = {1, -1, 0, 0}` để code sạch hơn và tránh sai sót khi duyệt 4 hoặc 8 ô xung quanh.
3.  **Biến đổi chỉ số:**
    *   Khi cần lưu ma trận vào các cấu trúc dữ liệu 1D (như Disjoint Set Union), hãy chuyển tọa độ $(r, c)$ thành một số nguyên duy nhất: `index = r * C + c`.
4.  **Tối ưu bộ nhớ:**
    *   Nếu $R \cdot C$ lớn nhưng chỉ cần thông tin của hàng trước đó (trong DP), hãy sử dụng **Mảng lăn (Rolling Array)** với 2 hàng để tiết kiệm bộ nhớ từ $O(R \cdot C)$ xuống $O(C)$.

#### Dấu hiệu nhận biết:
*   **Nếu $R$ rất nhỏ ($R \le 10$) nhưng $C$ rất lớn:** Hãy nghĩ ngay đến **DP Bitmask** trên cột hoặc **Nhân ma trận**.
*   **Nếu bài toán yêu cầu tìm hình chữ nhật lớn nhất:** Nghĩ đến kỹ thuật **Stack** (tương tự bài tìm hình chữ nhật lớn nhất trong biểu đồ).
### 7.5. Trường hợp hỗn hợp: Ma trận ($R \times C$) và $N$ vật thể/điểm đặc biệt

Đây là dạng bài "đánh lừa" cảm giác về độ phức tạp. Chìa khóa là xác định xem thuật toán sẽ chạy dựa trên **diện tích lưới** ($R \cdot C$) hay dựa trên **số lượng điểm** ($N$).

| Giới hạn biến | Độ phức tạp dự kiến | Hướng giải gợi ý |
| :--- | :--- | :--- |
| $R, C$ lớn ($10^9$), $N$ nhỏ ($10^5$) | $O(N \log N)$ hoặc $O(N^2)$ | **Nén tọa độ:** Biến lưới khổng lồ thành lưới ảo $N \times N$. |
| $R, C$ nhỏ ($100$), $N$ lớn ($10^5$) | $O(N + R \cdot C)$ | **Gom nhóm:** Xử lý $N$ điểm rồi đưa vào lưới để tính toán (như BFS loang). |
| $R, C$ trung bình, $N$ bước di chuyển | $O(R \cdot C \cdot N)$ | **DP 3D:** Trạng thái là `dp[hàng][cột][bước_thứ_n]`. |
| $R, C, N$ đều khoảng $100 \dots 200$ | $O(R \cdot C \cdot N)$ | **Hình hộp chữ nhật:** Xử lý như mảng 3 chiều. |

#### Các chiến thuật xử lý $R, C, N$ kết hợp:

1.  **Nén tọa độ (Coordinate Compression):**
    *   Nếu lưới cực lớn nhưng chỉ có $N$ điểm đáng chú ý, bạn chỉ cần quan tâm đến các dòng và các cột chứa $N$ điểm đó.
    *   Lưới $10^9 \times 10^9$ sẽ trở thành lưới tối đa $(2N) \times (2N)$.
    

2.  **Quản lý danh sách kề trên lưới:**
    *   Thay vì dùng `matrix[R][C]`, hãy dùng `vector<int> adj[R]` hoặc `map<pair<int, int>, int>` nếu lưới quá thưa để tiết kiệm bộ nhớ.

3.  **Kỹ thuật Quét ảnh (Sweeping Line):**
    *   Sắp xếp $N$ điểm theo tọa độ $R$ (hàng), sau đó dùng một cấu trúc dữ liệu (như Segment Tree) để xử lý theo chiều $C$ (cột). 
    *   Độ phức tạp thường là $O(N \log N)$ hoặc $O(N \log C)$.
    

4.  **Phân loại theo mật độ:**
    *   **Lưới dày ($N \approx R \cdot C$):** Ưu tiên các thuật toán duyệt trên toàn bộ ô lưới.
    *   **Lưới thưa ($N \ll R \cdot C$):** Ưu tiên các thuật toán dựa trên danh sách các điểm $N$ và bỏ qua các ô trống.

#### Dấu hiệu nhận biết hướng giải:
*   **Nếu $N$ là số truy vấn ($Q$):** Thường là bài toán Update/Query trên vùng hình chữ nhật (dùng 2D Fenwick hoặc 2D Segment Tree).
*   **Nếu $N$ là số vật cản:** Có thể là bài toán tìm đường đi ngắn nhất giữa các điểm đặc biệt (Dijkstra trên $N$ nút thay vì trên $R \cdot C$ ô).
---

## 8. Checklist tối ưu hóa khi "suýt" quá thời gian
Nếu thuật toán của bạn có vẻ đúng về độ phức tạp nhưng vẫn bị TLE:
- [ ] **Fast I/O:** Sử dụng `cin.tie(0)->sync_with_stdio(0);`
- [ ] **Hạn chế dùng Container phức tạp:** Thay `std::map` bằng `std::unordered_map` hoặc mảng tĩnh nếu có thể.
- [ ] **Tránh cấp phát động:** Sử dụng mảng toàn cục thay vì khai báo `vector` bên trong vòng lặp test case.
- [ ] **Pragma optimization:** Sử dụng `#pragma GCC optimize("O3,unroll-loops")` cho các bài toán tính toán thuần túy.