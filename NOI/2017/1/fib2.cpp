#include<bits/stdc++.h>

using namespace std;

int my_stoi(string s)
{
	int ret = 0;

	for(int i = 0; i < s.size(); i++)
	{
		ret *= 10;
		ret += s[i] - '0';
	}

	return ret;
}

struct Long
{
	vector<int> digits;

	Long()
	{
		digits.push_back(0);
	}

	Long(string value)
	{
		//cout << value << " value\n";

		for(int i = (int)value.size()-1; i >= 0; i--)
		{
			char x = value[i];
			digits.push_back(x - '0');
		}
	}

	Long(int value)
	{
		while(value >= 10)
		{
			digits.push_back(value % 10);
			value /= 10;
		}

		digits.push_back(value);
	}

	friend string to_string(Long value)
	{
		string ret;

		for(int i = value.digits.size() - 1; i >= 0; i--)
			ret += value.digits[i] + '0';

		return ret;
	}

	friend Long fix(Long num)
	{
		while((int)num.digits.size() > 1 && num.digits.back() == 0)
			num.digits.pop_back();

		return num;
	}

	friend bool operator<(Long lvalue, Long rvalue)
	{
		lvalue = fix(lvalue);
		rvalue = fix(rvalue);

		if(lvalue.digits.size() != rvalue.digits.size())
			return lvalue.digits.size() < rvalue.digits.size();

		for(int i = (int)lvalue.digits.size() - 1; i >= 0; i--)
			if(lvalue.digits[i] != rvalue.digits[i])
				return lvalue.digits[i] < rvalue.digits[i];

		return false;
	}

	friend bool operator>(Long lvalue, Long rvalue)
	{
		return rvalue < lvalue;
	}

	friend bool operator==(Long lvalue, Long rvalue)
	{
		return (lvalue < rvalue) == (rvalue < lvalue);
	}

	friend bool operator<=(Long lvalue, Long rvalue)
	{
		return !(lvalue > rvalue);
	}

	friend Long operator+(Long lvalue, Long rvalue)
	{
		int carry = 0;

		if(lvalue < rvalue)
			swap(lvalue, rvalue);

		for(int i = 0; i < (int)lvalue.digits.size(); i++)
		{
			if(i < (int)rvalue.digits.size())
				carry += rvalue.digits[i];
			lvalue.digits[i] += carry;
			carry = 0;

			if(lvalue.digits[i] >= 10)
			{
				lvalue.digits[i] -= 10;
				carry = 1;
			}
		}

		if(carry)
			lvalue.digits.push_back(carry);

		return fix(lvalue);
	}

	friend Long operator-(Long lvalue, Long rvalue)
	{
		int carry = 0;

		for(int i = 0; i < lvalue.digits.size(); i++)
		{
			if(i < rvalue.digits.size())
				carry -= rvalue.digits[i];
			lvalue.digits[i] += carry;

			carry = 0;

			if(lvalue.digits[i] < 0)
			{
				lvalue.digits[i] += 10;
				carry = -1;
			}
		}

		return fix(lvalue);
	}

	friend Long operator*(Long lvalue, Long rvalue)
	{
		Long ret;

		for(int i = 0; i < (int)lvalue.digits.size(); i++)
		{
			Long add;
			add.digits.resize(i, 0);

			int carry = 0;

			for(int j = 0; j < (int)rvalue.digits.size(); j++)
			{
				carry += lvalue.digits[i] * rvalue.digits[j];
				add.digits.push_back(carry % 10);
				carry /= 10;
			}
			if(carry)
				add.digits.push_back(carry);

			ret = ret + add;
		}

		return fix(ret);
	}

	friend Long operator/(Long lvalue, Long rvalue)
	{
		Long l = Long(), r = lvalue;

		//cout << l.digits.size() << " digits " << r.digits.size() << "\n";
		//cout << l.digits[0] << " zero " << r.digits[0] << "\n";
		//cout << (l < r) << " cmp\n";

		while(l < r)
		{
			Long mid = l + r + Long("1");

			//cout << to_string(l) << " l r " << to_string(r) << "\n";
			//cout << to_string(mid) << "\n";

			int carry = 0;

			for(int i = (int)mid.digits.size() - 1; i >= 0; i--)
			{
				carry = carry * 10 + mid.digits[i];
				mid.digits[i] = carry / 2;
				carry %= 2;
			}
			mid = fix(mid);

			//cout << to_string(mid) << " mid\n";

			if(mid * rvalue <= lvalue)
				l = mid;
			else
				r = mid - Long("1");
		}

		return l;
	}

	friend Long operator%(Long lvalue, Long rvalue)
	{
		return lvalue - (lvalue / rvalue) * rvalue; 
	}
};

long long to_int(char c)
{
	if('0' <= c && c <= '9')
		return c - '0';

	return c - 'A' + 10;
}

char to_char(long long x)
{
	if(x <= 9)
		return x + '0';

	return x - 10 + 'A';
}

struct num
{
	long long base;
	long long a, b;

	num(long long _base = 0)
	{
		base = _base;
	}

	friend istream& operator>>(istream &input, num &x)
	{
		string s;

		input >> s;

		if(s.size() == 1)
		{
			x.a = 0;
			x.b = to_int( s[s.size() - 1] );
		}
		else
		{
			x.b = to_int( s[s.size() - 1] );
			x.a = to_int( s[s.size() - 2] );
		}

		return input;
	}

	friend num operator+(num lhs, num rhs)
	{
		num res;

		res.base = lhs.base;
		res.b = (lhs.b + rhs.b) % res.base;

		long long carry = (lhs.b + rhs.b) / res.base;
		res.a = (lhs.a + rhs.a + carry) % res.base;

		return res;
	}

	friend bool operator<(num lhs, num rhs)
	{
		if(lhs.a < rhs.a)
			return true;
		if(lhs.a > rhs.a)
			return false;

		return lhs.b < rhs.b;
	}
};

const long long K = 100000;

map<pair<num, num>, long long> mp;
num f[K];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long p;
	string s;

	cin >> p >> s;

	Long n = Long(s);

	f[1] = num(p);
	f[2] = num(p);

	cin >> f[1] >> f[2];

	if(n == Long("1"))
	{
		cout << f[1].a << "\n";

		return 0;
	}

	if(n == Long("2"))
	{
		cout << f[2].a << "\n";

		return 0;
	}

	mp[ {f[1], f[2]} ] = 2;

	long long cycle = -1;

	for(long long i = 3; i < n; i++)
	{
		//cout << i << " i\n";

		f[i] = f[i-1] + f[i-2];

		if(mp.find( {f[i-1], f[i]} ) != mp.end())
		{
			cycle = i;
			break;
		}
		mp[ {f[i-1], f[i]} ] = i;
	}

	if(cycle == -1)
	{
		int n_num = my_stoi(to_string(n));

		//cout << n_num << endl;
		//cout << to_string(n) << endl;

		f[ n_num ] = f[ n_num - 1 ] + f[ n_num - 2 ];

		cout << to_char(f[ n_num ].a) << "\n";

		return 0;
	}

	n =  n - mp[ {f[cycle-1], f[cycle]} ];
	//cout << to_string(n) << "\n";
	n = n % (cycle - mp[ {f[cycle-1], f[cycle]} ]);
	//cout << to_string(n) << "\n";

	Long ind = n + mp[ { f[cycle-1] , f[cycle] } ];

	cout << to_char(f[ my_stoi(to_string(ind)) ].a) << "\n";

	return 0;
}
