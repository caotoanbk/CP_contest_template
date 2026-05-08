#include <bits/stdc++.h>
using namespace std;

using uint = unsigned;

// Kích thước lưới mô phỏng và số ô bàn sinh trước tối đa
const uint T = 2000;      // x, y ∈ [0, T)
const uint R = 200000;    // số lượng ô bàn tối đa trong thứ tự ưu tiên

// Ord: mảng lưu thứ tự ưu tiên các ô bàn (mã hóa p = x*T + y)
static uint Ord[R + 5];

// G[2][p]:
// - G[1][p] = true nếu ô bàn p đã bị chiếm (ti=1 không chọn được)
// - G[0][p] = true nếu ô bàn p không hợp lệ cho ti=0 vì bàn (block) đã bị chạm
static bool G[2][T * T];

// Con trỏ tiến cho hai chế độ ti = 0/1 trên mảng Ord
static uint Ans[2];

// Hàm sinh ô trong cùng bàn 2x2 từ ô bàn p theo bitmask o ∈ {0,1,2,3}
// o&1: flip theo trục y (giữa 3k+1 ↔ 3k+2)
// o&2: flip theo trục x (giữa 3k+1 ↔ 3k+2)
static inline uint Nxt(uint p, uint o) {
    uint x = p / T, y = p % T;
    if (o & 1) y = (y / 3) * 3 + (3 - (y % 3)); // y: 1->2, 2->1
    if (o & 2) x = (x / 3) * 3 + (3 - (x % 3)); // x: 1->2, 2->1
    return x * T + y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Tiền xử lý: sinh thứ tự ưu tiên các ô bàn vào Ord (tối đa R phần tử)
    // Ý tưởng: duyệt theo "lớp" i ~ x+y, phân tách theo i%3 để đảm bảo tie-break đúng.
    {
        uint tp = 0;
        for (uint i = 2; i < T && tp < R; ++i) {
            if (i % 3 == 2) {
                // Sinh các ô có dạng (x, y) với y = i và x%3 == 1
                for (uint x = 1; x < i && tp < R; x += 3) {
                    uint y = i - x;
                    Ord[tp++] = x * T + y;
                }
            } else if (i % 3 == 0) {
                // Sinh các ô với x từ 1..i-2
                for (uint x = 1; x <= i - 2 && tp < R; ++x) {
                    uint y = i - x;
                    if (x % 3 == 1) {
                        Ord[tp++] = x * T + y;
                    } else if (x % 3 == 2) {
                        // Hai vị trí để đáp ứng tie-break khi (x%3==2, y%3==2)
                        if (tp < R) Ord[tp++] = x * T + (y - 2);
                        if (tp < R) Ord[tp++] = x * T + y;
                    }
                }
                // Bổ sung một ô ở biên lớp để hoàn chỉnh thứ tự
                if (tp < R) Ord[tp++] = (i - 1) * T + 1;
            }
        }
    }

    // Xử lý testcases
    uint tc; 
    if (!(cin >> tc)) return 0;
    while (tc--) {
        uint q; 
        cin >> q;

        // Reset trạng thái G trên phạm vi cần thiết: q*4 ô đầu tiên của Ord
        for (uint i = 0; i < q * 4; ++i) {
            uint p = Ord[i];
            G[0][p] = false;
            G[1][p] = false;
        }
        Ans[0] = 0;
        Ans[1] = 0;

        while (q--) {
            uint ti; 
            cin >> ti;           // 0: chọn bàn trống hoàn toàn; 1: chọn ô bàn trống bất kỳ
            uint &ptr = Ans[ti]; // con trỏ theo chế độ ti

            // Tìm ô phù hợp đầu tiên (bỏ qua các ô bị đánh dấu G[ti])
            while (G[ti][Ord[ptr]]) ++ptr;

            uint p = Ord[ptr];
            uint x = p / T, y = p % T;
            cout << x << " " << y << "\n";

            // Đánh dấu ô đã chiếm (cho ti=1)
            G[1][p] = true;

            // Đánh dấu bàn đã bị chạm (4 ô trong cùng bàn) là không hợp lệ cho ti=0
            for (uint o = 0; o < 4; ++o) {
                uint qp = Nxt(p, o);
                G[0][qp] = true;
            }
        }
    }

    return 0;
}