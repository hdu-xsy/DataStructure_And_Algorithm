package Algorithm;

import java.util.Arrays;

public class LCS {

    public String LCS(String s1, String s2) {
        int len1 = s1.length();
        int len2 = s2.length();
        /* 状态定义 */
        int[][] dp = new int[len1+1][len2+1];
        /* 状态初始化 */
        /**
         *x/y| 0 1 2 3
         *  -|－－－－－
         *  0| 0 0 0 0
         *  1| 0
         *  2| 0
         *  3| 0
         * */
        for (int i = 0; i < len2 + 1; i++) dp[0][i] = 0;
        for (int i = 0; i < len1 + 1; i++) dp[i][0] = 0;
        /* dp状态的推导 */
        /**
         * c[i,j] = c[i-1][j-1] + 1 , xi = yj
         * c[i,j] = max(c[i,j-1],c[i-1,j]) xi != yj
         * */
        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                if(s1.charAt(i) == s2.charAt(j)) dp[i+1][j+1] = dp[i][j] + 1;
                else dp[i+1][j+1] = Math.max(dp[i][j+1],dp[i+1][j]);
            }
        }
        for (int i = 0; i < len1 + 1; i++) System.out.println(Arrays.toString(dp[i]));
        int x = len1,y = len2;
        StringBuilder sb = new StringBuilder();
        while(x != 0 || y != 0) {
            if(dp[x][y-1] == dp[x][y]) y = y-1;
            else if(dp[x-1][y] == dp[x][y]) x = x-1;
            else {
                sb.append(s1.charAt(x-1));
                x--;
                y--;
            }
        }
        return new String(sb.reverse());
    }

}
