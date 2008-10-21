/* Genus 2 arithmetic demo cgi */

#include <sys/timeb.h>
#include <errno.h>
#include <time.h>
#include <g2hec_Genus2_ops.h>
#include <g2hec_rand.h>
#include <g2hec_nsdebug.h>

#undef MAX_STRING_LEN
#define MAX_STRING_LEN 500

/* Global data */
char p[MAX_STRING_LEN];
char h2[MAX_STRING_LEN], h1[MAX_STRING_LEN], h0[MAX_STRING_LEN];
char f5[MAX_STRING_LEN],f4[MAX_STRING_LEN],f3[MAX_STRING_LEN],
  f2[MAX_STRING_LEN],f1[MAX_STRING_LEN],f0[MAX_STRING_LEN];
char u2[MAX_STRING_LEN], u1[MAX_STRING_LEN], u0[MAX_STRING_LEN];
char v1[MAX_STRING_LEN], v0[MAX_STRING_LEN];
size_t primesize;
char n[MAX_STRING_LEN];
char buttontype[MAX_STRING_LEN];

NS_G2_CLIENT

/* Subroutine to generate random prime, curve and divisor */
static void generate_random() 
{
  ZZ prime, scalar; 

  /* PRNG seeding */
  SetSeed(g2hec_rand()); // Get random seed from /dev/urandom.

  RandomPrime(prime, (long) primesize, 10);
  RandomBnd(scalar, prime);

  field_t::init(prime);

  poly_t f, h, u, v;

  g2hcurve curve;

  divisor div;

  curve.random();

  div.set_curve(curve);

  div.random();

  f = curve.get_f();

  h = curve.get_h();

  u = div.get_upoly();

  v = div.get_vpoly();

  /* Print web page */

  cout << "<!-- Genus 2 arithmetic demo -->" << endl;
  cout << "<html>" << endl << endl
  << "<head>" << endl
  << "<meta http-equiv=\"Content-Type\" content=\"text/html; \
charset=utf-8\" />" << endl 
  << "<script language=\"javascript\" type=\"text/javascript\" src=\"tools.js\">" << endl
  << "</script>" << endl

  << endl << "<!-- Workaround for IE7 prompt() blocking -->" << endl
  << "<script language=\"javascript\" type=\"text/javascript\" src=\"IEprompt.js\">" << endl
  << "</script>" << endl

  << "<script language=\"javascript\" type=\"text/javascript\" src=\"promptcb.js\">" << endl
  << "</script>" << endl

  << "<title> Genus 2 arithmetic demo </title>" << endl
  << "</head>" << endl
  << "<body>" << endl
  << "<form name=\"demoform\" method=\"POST\" action=\"arithdemo.cgi\">" << endl
  << "<div>" << endl
  << "<label><h4>libg2hec Demo: genus 2 curve C: y^2+h(x)y=f(x) over GF(p)\
scalar multiplication</h4></label>" << endl
  << "</div>" << endl
  << "<hr />" << endl

  <<"<div>" << endl
  << "<label> prime p = </label>" << endl
  << "<textarea name=\"p\" cols=\"60\" rows=\"3\" id=\"p\" wrap=\"virtual\">" 
  << prime 
  << "</textarea>" << endl
       << "</div>" << endl

       << "<div>" << endl

       << "<label>h(x) = </label>" << endl

       << "<textarea name=\"h2\" cols=\"10\" rows=\"1\" id=\"h2\" wrap=\"virtual\">" 
       << coeff(h, 2) 
       << "</textarea> x^2 + <textarea name=\"h1\" cols=\"10\" rows=\"1\" id=\"h1\" wrap=\"virtual\">" 
       << coeff(h, 1) 
       << "</textarea> x + <textarea name=\"h0\" cols=\"10\" rows=\"1\" id=\"h0\" wrap=\"virtual\">"
       << coeff(h, 0) << "</textarea>" << endl;
  
  cout << "</div>" << endl;

  cout << "<div>" << endl;

  cout << "<label>f(x) = </label>" << endl;

  cout << "x^5 + "  
       << "<textarea name=\"f4\" cols=\"10\" rows=\"1\" id=\"f4\" wrap=\"virtual\">"
       << coeff(f, 4) << "</textarea> x^4 + "
       << "<textarea name=\"f3\" cols=\"10\" rows=\"1\" id=\"f3\" wrap=\"virtual\">"
       << coeff(f, 3) <<"</textarea> x^3 + "
       << "<textarea name=\"f2\" cols=\"10\" rows=\"1\" id=\"f2\" wrap=\"virtual\">"
       << coeff(f, 2) <<"</textarea> x^2 + "
       << "<textarea name=\"f1\" cols=\"10\" rows=\"1\" id=\"f1\" wrap=\"virtual\">"
       << coeff(f, 1) << "</textarea> x + "
       << "<textarea name=\"f0\" cols=\"10\" rows=\"1\" id=\"f0\" wrap=\"virtual\">"
       << coeff(f, 0) << "</textarea>" << endl;

  cout << "</div>" << endl;

  cout << "<br />" << endl;

  cout << "<div>" << endl;

  cout << "divisor D = [u(x), v(x)]" << endl;
  cout << "</div>" << endl;

  cout << "<div>" << endl;

  cout << "<label> u(x) = </label>" << endl;
  cout << "<textarea name=\"u2\" cols=\"10\" rows=\"1\" id=\"u2\" wrap=\"virtual\">"
       << coeff(u, 2) << "</textarea> x^2 + "
       << "<textarea name=\"u1\" cols=\"10\" rows=\"1\" id=\"u1\" wrap=\"virtual\">"
       << coeff(u, 1) << "</textarea> x + "
       << "<textarea name=\"u0\" cols=\"10\" rows=\"1\" id=\"u0\" wrap=\"virtual\">"
       << coeff(u, 0) << "</textarea>" << endl;
  cout << "</div>" << endl;

  cout << "<div>" << endl;

  cout << "<label> v(x) = </label>" << endl;
  cout << "<textarea name=\"v1\" cols=\"10\" rows=\"1\" id=\"v1\" wrap=\"virtual\">"
       << coeff(v, 1) << "</textarea> x + "
       << "<textarea name=\"v0\" cols=\"10\" rows=\"1\" id=\"v0\" wrap=\"virtual\">"
       << coeff(v, 0) << "</textarea>" << endl;
  cout << "</div>" << endl;

  cout << "<br />" << endl;

  cout << "<div>" << endl;

  cout << "<label> scalar n = </label>" << endl;

  cout << "<textarea name=\"n\" cols=\"60\" rows=\"3\" id=\"n\" wrap=\"virtual\">"
       << scalar << "</textarea>" << endl;
  
  cout << "<hr />" << endl << "<br />" << endl;

  cout << "</div>" << endl;

  cout << "<div>" << endl;
  cout << "<input type=\"hidden\" name=\"primesize\" value=\""
       << primesize << "\" />" << endl;
  cout << "<input type=\"hidden\" name=\"buttontype\" />" << endl;

  cout << "<input type=\"button\" value=\"Choose random\" onClick=\'Choose_prime_size()\'/>" << endl;

  cout << "<input type=\"button\" value=\"Reset\" onClick=\'self.location=\"demo.html\"\' />" << endl;

  cout << "<input type=\"button\" value=\"Calculate [n]D\" onClick=\'Calculate()\' />" << endl;
  cout << "</div>" << endl;
  cout << "</form>" << endl;

  cout << "</body>" << endl;

   cout <<   " </html>" << endl;

  /* End print web page */

} 

/* Subroutine to do computation */
static void calculate()
{
    /* Primility test */
    if (! ProbPrime(to_ZZ(p)) ) {
      cout << "p = " << p << " is not prime";
      exit(1);
    }

    struct timeb start, finish;

    int rc_start, rc_finish;

    field_t::init(to_ZZ(p));

    poly_t f, h, u, v;

    g2hcurve curve;

    divisor div, div_out;

    SetCoeff(f, 5, 1);
    SetCoeff(f, 4, to_ZZ_p(to_ZZ(f4)));
    SetCoeff(f, 3, to_ZZ_p(to_ZZ(f3)));
    SetCoeff(f, 2, to_ZZ_p(to_ZZ(f2)));
    SetCoeff(f, 1, to_ZZ_p(to_ZZ(f1)));
    SetCoeff(f, 0, to_ZZ_p(to_ZZ(f0)));

    SetCoeff(h, 2, to_ZZ_p(to_ZZ(h2)));
    SetCoeff(h, 1, to_ZZ_p(to_ZZ(h1)));
    SetCoeff(h, 0, to_ZZ_p(to_ZZ(h0)));

    SetCoeff(u, 2, to_ZZ_p(to_ZZ(u2)));
    SetCoeff(u, 1, to_ZZ_p(to_ZZ(u1)));
    SetCoeff(u, 0, to_ZZ_p(to_ZZ(u0)));

    SetCoeff(v, 1, to_ZZ_p(to_ZZ(v1)));
    SetCoeff(v, 0, to_ZZ_p(to_ZZ(v0)));

    curve.set_h(h);
    curve.set_f(f);
    curve.update();

    if (!curve.is_valid_curve()) {
      cout << "<p>Curve is not valid</p>" << endl;
      exit(1);
    }

    div.set_curve(curve);
    div.set_upoly(u);
    div.set_vpoly(v);
    div.update();

    if (!div.is_valid_divisor()) {
      cout << "<p>Divisor D is not valid</p>" << endl;
      cout << div << endl;
      exit(1);
    }

    ZZ nn = to_ZZ(n);

    /* scalar multiplication: NAF */
    rc_start = ftime(&start);

    if (rc_start) {
      printf("ftime() failed, errno = %d\n",
             errno);
      exit(1);
    }

    /* Actuall computation */
    scalar_mul(div_out, div, nn, NAF);
    /* End of computation */

    rc_finish = ftime(&finish);

    if (rc_finish) {
      printf("ftime() failed, errno = %d\n",
             errno);
      exit(1);
    }

    /* Time in seconds */
    double time = finish.time-start.time;
    time *= 1000;
    time += finish.millitm-start.millitm;
    time /= 1000;

    /* print html page */
    cout << "<!-- Scalar multiplication result -->" << endl
	 << "<html>" << endl << endl
	 << "<head>" << endl
	 << "<title>Scalar multiplication result</title>" << endl
	 << "</head>" << endl << endl

	 << "<body>" << endl

	 << "<h4>Scalar multiplication result</h4>" << endl
	 << "<div>Genus 2 curve C: y^2+h(x)y=f(x) over GF(p)</div>" << endl
	 << "<div>" << primesize << "-bit prime p = " << p << endl
	 << "<hr />" << endl

	 << "<pre>" << endl

	 << "input divisor D: " << endl
	 << "<pre>" << endl
	 << div << endl
	 << "input scalar n = " << n << endl
	 << "<hr />" << endl

	 << "output divisor [n]D: " << endl
	 << div_out << endl
         << "Computation took " << time << " sec " << endl
	 << "<hr />" << endl
	 << "</pre>" << endl
      /* "Back button" */
	 << "<form><input type=\"button\" value=\" &lt;-- Back \" onClick=\"history.go(-1);return false;\" /></form>" << endl
 
	 << "</body>" << endl
	 << "</html>" << endl;

    /* end print html page*/
}


int main() 
{ /* The following must be the first line of output */
  printf("%s%c%c\n\n", "Content-Type:text/html; charset=utf-8", 13, 10);
  
  if (!getenv("CONTENT_LENGTH")) {
    cout << "Error reading data" << endl;
    exit(1);
  }  

  char data[MAX_STRING_LEN*20];
  int datalen = atoi( getenv("CONTENT_LENGTH") );
  fread(data, datalen, 1, stdin);

  /* for GET method */
  /* data = getenv("QUERY_STRING"); */

  if (!data) cout << "<p>Error reading data</p>" << endl;
  else if (sscanf(data, "p=%[0-9]&h2=%[0-9]&h1=%[0-9]&h0=%[0-9]&f4=%[0-9]&\
f3=%[0-9]&f2=%[0-9]&f1=%[0-9]&f0=%[0-9]&u2=%[0-9]&u1=%[0-9]&u0=%[0-9]&\
v1=%[0-9]&v0=%[0-9]&n=%[0-9-]&primesize=%u&buttontype=%s", p, h2, h1, h0, \
f4, f3, f2, f1, f0, u2, u1, u0, v1, v0, n, &primesize, buttontype) != 17) \
                                cout << "<p>Invalid input data. </p>" << endl;

  else {
    if ( !strcmp(buttontype, "Random") ) generate_random();

    if (!strcmp(buttontype, "Calculate") ) calculate();
  }

  return 0;
}
