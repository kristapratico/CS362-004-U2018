
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!






public class UrlValidatorTest extends TestCase {
	
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
   
	   UrlValidator url = new UrlValidator();
	   
	   assertTrue(url.isValid("http://www.neopets.com"));
	   System.out.println(url.isValid("http://"));
   }
   
   
   public void testScheme()
   {
	   String url = "www.neopets.com";
	   UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validScheme = {"http://", "ftp://", "h3t://", "https://", "ftp://", ""};
       String[] invalidScheme = {"3ht://", "http:/", "http:", "http/", "://"};
       System.out.println("Partition Testing: Scheme");
       System.out.println("\n" + "Valid Schemes");
       for (int x = 0; x < validScheme.length; x++) {
    	   System.out.println(validScheme[x] + url + ": " + testUrl.isValid(validScheme[x] + url));
    	   //assertEquals(true, testUrl.isValid(validScheme[x] + url));

       }
       
       System.out.println("\n" + "Invalid Schemes");
       for (int x = 0; x < invalidScheme.length; x++) {
    	   System.out.println(invalidScheme[x] + url + ": " + testUrl.isValid(invalidScheme[x] + url));
    	   //assertEquals(true, testUrl.isValid(invalidScheme[x] + url));
       }
       
   }
   
   public void testAuthority()
   {
	   String url = "http://";
	   UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validAuth = {"www.google.com", "www.neopets.com", "0.0.0.0", "256.255.255.256", "www.amazon.com", "go.com"};
       String[] invalidAuth = {"zyx", ".1.2.3", "go.b", "yyy.", ""};
       System.out.println("\n" + "Partition Testing: Authority");
       System.out.println("\n" + "Valid Authoritys");
       for (int x = 0; x < validAuth.length; x++) {
    	   System.out.println(url + validAuth[x] + ": " + testUrl.isValid(url + validAuth[x]));
    	   //assertEquals(true, testUrl.isValid(validAuth[x] + url));

       }
       
       System.out.println("\n" + "Invalid Authoritys");
       for (int x = 0; x < invalidAuth.length; x++) {
    	   System.out.println(url + invalidAuth[x] + ": " + testUrl.isValid(url + invalidAuth[x]));
    	   //assertEquals(true, testUrl.isValid(invalidAuth[x] + url));
       }

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
