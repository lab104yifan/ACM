import java.util.*;
import java.math.*;
import java.io.*;

public class UVA10458 {
	public static int bitcount(int x) {
		int ans = 0;
		while (x > 0) {
			ans += (x&1);
			x >>= 1;
		}
		return ans;
	}
	
	public static BigInteger C(long n, int m) {
		BigInteger ans;
		ans = BigInteger.valueOf(1);
		for (int i = 0; i < m; i++)
			ans = ans.multiply(BigInteger.valueOf(n - i)).divide(BigInteger.valueOf(i + 1));
		return ans;
	}

	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		int n;
		long sum;
		long[] a;
		a = new long[10];
		while (cin.hasNext()) {
			n = cin.nextInt();
			sum = cin.nextLong();
			long tmp;
			for (int i = 0; i < n; i++) {
				tmp = cin.nextLong();
				a[i] = cin.nextLong();
				a[i] -= tmp;
				sum -= tmp;
			}
			Arrays.sort(a);
			for (int i = 0; i < n; i++) {
				System.out.print(a[i]);
				System.out.print(" ");
			}
			System.out.print("\n");
			BigInteger ans;
			ans = BigInteger.valueOf(0);
			for (int i = 0; i < (1<<n); i++) {
				long s = sum;
				for (int j = 0; j < n; j++) {
					if ((i&(1<<j)) != 0) {
						s -= a[j] + 1;
					}
					if (s < 0) break;
				}
				if (s < 0) continue;
				if ((bitcount(i)&1) != 0) ans = ans.subtract(C(s + n - 1, n - 1));
				else ans = ans.add(C(s + n - 1, n - 1));
			}
			System.out.println(ans);
		}
	}
}
