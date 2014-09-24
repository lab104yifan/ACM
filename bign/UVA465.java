import java.util.*;
import java.io.*;
import java.math.*;

public class UVA465 {
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		BigInteger a1, b1, sum, tmp = BigInteger.valueOf(2147483647);
		String a, b, c;
		while (cin.hasNext()) {
			a = cin.next();
			c = cin.next();
			b = cin.next();
			a1 = new BigInteger(a);
			b1 = new BigInteger(b);
			System.out.println(a + ' ' + c + ' ' + b);
			if (c.equals("+")) sum = a1.add(b1);
			else sum = a1.multiply(b1);
			if (a1.compareTo(tmp) > 0)
				System.out.println("first number too big");
			if (b1.compareTo(tmp) > 0)
				System.out.println("second number too big");
			if (sum.compareTo(tmp) > 0)
				System.out.println("result too big");
		}
	}
}
