import java.io.*;
import java.math.*;
import java.util.*;

public class UVA10494 {
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		BigInteger a, b;
		String c;
		while (cin.hasNext()) {
			a = BigInteger.valueOf(1);
			a = cin.nextBigInteger();
			c = cin.next();
			b = cin.nextBigInteger();
			BigInteger res;
			if (c.equals("/")) res = a.divide(b);
			else res = a.mod(b);
			System.out.println(res);
		}
	}
}
