import java.util.*;
import java.math.*;
import java.io.*;

public class UVA10106 {
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		while (cin.hasNext()) {
			BigInteger a = cin.nextBigInteger();
			BigInteger b = cin.nextBigInteger();
			System.out.println(a.multiply(b));
		}
	}
}
