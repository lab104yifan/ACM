import java.util.*;
import java.math.*;
import java.io.*;

public class UVA748 {
	public static BigDecimal pow(BigDecimal x, int k) {
		BigDecimal ans;
		ans = BigDecimal.valueOf(1.0);
		while (k > 0) {
			if (k % 2 == 1) ans = ans.multiply(x);
			x = x.multiply(x);
			k >>= 1;
		}
		return ans;
	}

	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		BigDecimal x;
		int k;
		while (cin.hasNext()) {
			x = cin.nextBigDecimal();
			k = cin.nextInt();
			BigDecimal ans = pow(x, k);
			String res = ans.stripTrailingZeros().toPlainString();
			if (res.charAt(0) == '0') res = res.substring(1);
			System.out.println(res);
		}
	}
}
