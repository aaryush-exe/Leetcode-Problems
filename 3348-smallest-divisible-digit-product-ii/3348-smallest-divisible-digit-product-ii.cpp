class Solution {
public:
    int factor[10][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 1},
        {3, 0, 0, 0},
        {0, 2, 0, 0}
    };

    int sum(int a[4]) {
        return a[0] + a[1] + a[2] + a[3];
    }

    void subtract(int a[4], int b[4]) {
        for (int i = 0; i < 4; i++)
            a[i] = max(0, a[i] - b[i]);
    }

    void getDigits(int cnt[4], int res[10]) {
        int c2 = cnt[0];
        int c3 = cnt[1];

        for (int i = 0; i < 10; i++)
            res[i] = 0;

        res[5] = cnt[2];
        res[7] = cnt[3];

        res[8] = c2 / 3;
        c2 %= 3;

        res[9] = c3 / 2;
        c3 %= 2;

        res[4] = c2 / 2;
        c2 %= 2;

        if (c2 == 1 && c3 == 1) {
            res[6]++;
            c2 = 0;
            c3 = 0;
        }

        if (c3 == 1 && res[4] == 1) {
            res[4] = 0;
            res[6]++;
            res[2]++;
            c3 = 0;
        }

        res[2] += c2;
        res[3] += c3;
    }

    string construct(int cnt[4]) {
        int digits[10];
        getDigits(cnt, digits);

        string ans;

        for (int d = 2; d <= 9; d++)
            ans += string(digits[d], char('0' + d));

        return ans;
    }

    string smallestNumber(string num, long long t) {
        int need[4] = {0, 0, 0, 0};
        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {
            while (t % primes[i] == 0) {
                need[i]++;
                t /= primes[i];
            }
        }

        if (t != 1)
            return "-1";

        int requiredDigits[10];
        getDigits(need, requiredDigits);

        int minLength = 0;

        for (int d = 2; d <= 9; d++)
            minLength += requiredDigits[d];

        if (minLength > num.size())
            return construct(need);

        int have[4] = {0, 0, 0, 0};

        for (char ch : num) {
            int d = ch - '0';

            for (int j = 0; j < 4; j++)
                have[j] += factor[d][j];
        }

        bool hasZero = false;

        for (char ch : num) {
            if (ch == '0') {
                hasZero = true;
                break;
            }
        }

        if (!hasZero) {
            bool ok = true;

            for (int i = 0; i < 4; i++) {
                if (have[i] < need[i])
                    ok = false;
            }

            if (ok)
                return num;
        }

        int firstZero = num.find('0');

        if (firstZero == string::npos)
            firstZero = num.size();

        int suffix[4] = {0, 0, 0, 0};

        for (int i = num.size() - 1; i >= 0; i--) {
            int d = num[i] - '0';

            for (int j = 0; j < 4; j++)
                have[j] -= factor[d][j];

            int space = num.size() - 1 - i;

            if (i > firstZero)
                continue;

            for (int bigger = d + 1; bigger <= 9; bigger++) {
                int required[4];

                for (int j = 0; j < 4; j++) {
                    required[j] =
                        max(0, need[j] - have[j] - factor[bigger][j]);
                }

                int digits[10];
                getDigits(required, digits);

                int count = 0;

                for (int x = 2; x <= 9; x++)
                    count += digits[x];

                if (count <= space) {
                    string ans = num.substr(0, i);

                    ans += char('0' + bigger);

                    ans += string(space - count, '1');

                    for (int x = 2; x <= 9; x++)
                        ans += string(digits[x], char('0' + x));

                    return ans;
                }
            }
        }

        return string(num.size() + 1 - minLength, '1') +
               construct(need);
    }
};