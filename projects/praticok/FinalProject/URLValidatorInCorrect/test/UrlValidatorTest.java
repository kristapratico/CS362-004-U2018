
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
   
	   UrlValidator url = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   assertTrue(url.isValid("http://www.google.com@action=view"));
   }
   
   
   public void testScheme()
   {
	   String url = "www.google.com";
	   UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
       String[] validScheme = {"http://", "ftp://", "h3t://", "https://", "ftp://", ""};
       String[] invalidScheme = {"3ht://", "http:/", "http:", "http/", "://"};
       System.out.println("\n" + "Partition Testing: Scheme");
       System.out.println("\n" + "Valid Schemes");
       for (int x = 0; x < validScheme.length; x++) {
    	   System.out.println(validScheme[x] + url + " : " + testUrl.isValid(validScheme[x] + url));
       }
       
       System.out.println("\n" + "Invalid Schemes");
       for (int x = 0; x < invalidScheme.length; x++) {
    	   System.out.println(invalidScheme[x] + url + " : " + testUrl.isValid(invalidScheme[x] + url));
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
    	   System.out.println(url + validAuth[x] + " : " + testUrl.isValid(url + validAuth[x]));
       }
       
       System.out.println("\n" + "Invalid Authoritys");
       for (int x = 0; x < invalidAuth.length; x++) {
    	   System.out.println(url + invalidAuth[x] + " : " + testUrl.isValid(url + invalidAuth[x]));
       }

   }

   public void testPort()
   {
	   String url = "http://www.google.com";
	   UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
       String[] validPort = {":80", ":900", ":483", ":65535", ":0", ""};
       String[] invalidPort = {":-2", ":9a", ":70000", ":-54a"};
       System.out.println("\n" + "Partition Testing: Port");
       System.out.println("\n" + "Valid Ports");
       for (int x = 0; x < validPort.length; x++) {
    	   System.out.println(url + validPort[x] + " : " + testUrl.isValid(url + validPort[x]));

       }
       
       System.out.println("\n" + "Invalid Ports");
       for (int x = 0; x < invalidPort.length; x++) {
    	   System.out.println(url + invalidPort[x] + " : " + testUrl.isValid(url + invalidPort[x]));
       }
       
   }
   
   public void testPath()
   {
	   String url = "http://www.google.com";
	   UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
       String[] validPath = {"/path", "/test123", "/test/file", "/path/"};
       String[] invalidPath = {"/.../", "//test//", "/.-./", "/test..//"};
       System.out.println("\n" + "Partition Testing: Path");
       System.out.println("\n" + "Valid Paths");
       for (int x = 0; x < validPath.length; x++) {
    	   System.out.println(url + validPath[x] + " : " + testUrl.isValid(url + validPath[x]));

       }
       
       System.out.println("\n" + "Invalid Paths");
       for (int x = 0; x < invalidPath.length; x++) {
    	   System.out.println(url + invalidPath[x] + " : " + testUrl.isValid(url + invalidPath[x]));
       }
       
   }
   
   public void testQuery()
   {
	   String url = "http://www.google.com";
	   UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
       String[] validQuery = {"?action=view", "?action=edit&mode=up", ""};
       String[] invalidQuery = {"@action=view", "@action=edit&mode=up"};
       System.out.println("\n" + "Partition Testing: Query");
       System.out.println("\n" + "Valid Queries");
       for (int x = 0; x < validQuery.length; x++) {
    	   System.out.println(url + validQuery[x] + " : " + testUrl.isValid(url + validQuery[x]));

       }
       
       System.out.println("\n" + "Invalid Queries");
       for (int x = 0; x < invalidQuery.length; x++) {
    	   System.out.println(url + invalidQuery[x] + " : " + testUrl.isValid(url + invalidQuery[x]));
       }
       
   }
   
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
