

class PrimeFactorization {

public:
    static std::multiset<ll> primeFactorization(ll n)
    {
        std::multiset<ll> factors;
        if (n <= 0)
            throw std::invalid_argument("Invalid input");
        else if (n == 1)
            return factors;
        auto longComparer = [](ll a, ll b) -> bool { return a > b; };
        std::priority_queue<long, std::vector<long>, decltype(longComparer)> divisorQueue(longComparer);
        divisorQueue.push(n);
        while (divisorQueue.size() > 0) {
            long divisor = divisorQueue.top();
            divisorQueue.pop();
            if (isPrime(divisor)) {
                factors.insert(divisor);
                continue;
            }
            long next_divisor = pollardRho(divisor);
            if (next_divisor == divisor) {
                divisorQueue.push(divisor);
            } else {
                divisorQueue.push(next_divisor);
                divisorQueue.push(divisor / next_divisor);
            }
        }
        return factors;
    }

private:
    static ll genRandInt(ll start_in, ll end_in)
    {
        // engine only provides a source of randomness
        std::mt19937_64 rng;
        // initialize the random number generator with time-dependent seed
        uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::seed_seq ss { uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
        rng.seed(ss);
        std::uniform_int_distribution<ll> dist(start_in, end_in);

        return dist(rng);
    }

    static long pollardRho(ll n)
    {
        if (n % 2 == 0)
            return 2;
        ll x = 2 + (ll)genRandInt(0, 999999);
        ll c = 2 + (ll)genRandInt(0, 999999);
        ll y = x;
        ll d = 1;
        while (d == 1) {
            x = (x * x + c) % n;
            y = (y * y + c) % n;
            y = (y * y + c) % n;
            d = gcd(abs(x - y), n);
            if (d == n)
                break;
        }
        return d;
    }

    static ll gcd(ll a, ll b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    static bool isPrime(ll n)
    {
        if (n < 2)
            return false;
        if (n == 2 || n == 3)
            return true;
        if (n % 2 == 0 || n % 3 == 0)
            return false;
        ll limit = (ll)sqrt(n);
        for (ll i = 5; i <= limit; i += 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        return true;
    }
};

int main()
{
    ll n;
    while (sfl(n) && n) {
        map<ll, int> mp;
        PrimeFactorization pr;
        multiset<ll> a = pr.primeFactorization(n);

        //for(long i =0;  i< (long)a.size();i++){
        //mp[a()]++;
        //}
        for (multiset<ll>::iterator it = a.begin(); it != a.end(); ++it) {
            mp[*it]++;
        }

        for (auto x : mp) {
            cout << x.first << "^" << x.second << " ";
        }
        cout << "\n";
    }
    return 0;
}
