import java.util.*;
import java.math.*;
import java.io.*;

public class UVA424 {
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		BigInteger a, sum;
		sum = BigInteger.ZERO;
		while (cin.hasNext()) {
			a = cin.nextBigInteger();
			if (a.equals(BigInteger.ZERO)) break;
			sum = sum.add(a);
		}
		System.out.println(sum);
	}
}
