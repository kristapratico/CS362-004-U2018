
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
     //instantiate urlValidator with constructor
     //UrlValidator urlVal = new UrlValidator();
     UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
     
     // String schemes[] = { "http", "https", "ftp" };
     // UrlValidator urlVal = new UrlValidator(schemes);
     
     //note the match pattern: 
     //scheme://host:port/path?query
     
     //testing random websites
     System.out.println(urlVal.isValid("https://oregonstate.instructure.com/courses/1683590"));
     System.out.println(urlVal.isValid("neopets.com"));
     System.out.println(urlVal.isValid("https://piazza.com/class/jino9xi6ivg1h3?cid=103"));
     System.out.println(urlVal.isValid("http://neopets.com"));
     System.out.println(urlVal.isValid("neopets.com?jubjub"));
     System.out.println(urlVal.isValid("https://osu-cs.slack.com/"));
     System.out.println(urlVal.isValid(""));
     System.out.println(urlVal.isValid("ftp://foo.bar.com/"));
     System.out.println(urlVal.isValid("http://www.google.com/"));
     System.out.println(urlVal.isValid("http://www.amazon.com/"));
     
     //notice that both true and false URLs output false
     //different constructor lead to different outputs
     //allow_all_schemes errors out for ftp and https, but not http
	   
   }
   
   // TEST PARTITION: SCHEME
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
   
   // TEST PARTITION: AUTHORITY
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
   
   // TEST PARTITION: PORT
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

   // TEST PARTITION: PATH
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
   
   // TEST PARTITION: QUERY
   public void testQuery()
   {
       String url = "http://www.google.com";
       UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	  
       String[] validQuery = {"?action=view", "?action=edit&mode=up", ""};
       String[] invalidQuery = {"@action=view", "!action=edit&mode=up"};
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
       String[] validScheme = {"http://", "ftp://", "h3t://", "https://", "ftp://", ""};
       String[] invalidScheme = {"3ht://", "http:/", "http:", "http/", "://"};
       String[] validAuth = {"www.google.com", "www.neopets.com", "0.0.0.0", "256.255.255.256", "www.amazon.com", "go.com"};
       String[] invalidAuth = {"zyx", ".1.2.3", "go.b", "yyy.", ""};
       String[] validPort = {":80", ":900", ":483", ":65535", ":0", ""};
       String[] invalidPort = {":-2", ":9a", ":70000", ":-54a"};
       String[] validPath = {"/path", "/test123", "/test/file", "/path/"};
       String[] invalidPath = {"/.../", "//test//", "/.-./", "/test..//"};
       String[] validQuery = {"?action=view", "?action=edit&mode=up", ""};
       String[] invalidQuery = {"@action=view", "@action=edit&mode=up"};
       
       String url;
       String scheme;
       String authority;
       String port;
       String path;
       String query;
       
       UrlValidator testUrl = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("\nUnit Tests");
       System.out.println("\nInvalid URL's"); 
       for (int i = 0; i < invalidScheme.length; i++) {
    	   url = "";
    	   url += invalidScheme[i];
    	   scheme = url;
    	   for (int j = 0; j < invalidAuth.length; j++) {
    		   url = scheme;
    		   url += invalidAuth[j];
        	   authority = url;
        	   for (int k = 0; k < invalidPort.length; k++) {
        		   url = authority;
            	   url += invalidPort[k];
            	   port = url;
            	   for (int l = 0; l < invalidPath.length; l++) {
            		   url = port;
                	   url += invalidPath[l];
                	   path = url;
                	   for (int m = 0; m < invalidQuery.length; m++) {
                		   url = path;
                    	   url += invalidQuery[m];
                    	   System.out.println(url + " : " + testUrl.isValid(url));

                       }
                   }
               }
           }
       }
       
       scheme = "";
       authority = "";
       port = "";
       path = "";

       System.out.println("\nValid URL's"); 
       for (int i = 0; i < validScheme.length; i++) {
    	   url = "";
    	   url += validScheme[i];
    	   scheme = url;
    	   for (int j = 0; j < validAuth.length; j++) {
    		   url = scheme;
    		   url += validAuth[j];
        	   authority = url;
        	   for (int k = 0; k < validPort.length; k++) {
        		   url = authority;
            	   url += validPort[k];
            	   port = url;
            	   for (int l = 0; l < validPath.length; l++) {
            		   url = port;
                	   url += validPath[l];
                	   path = url;
                	   for (int m = 0; m < validQuery.length; m++) {
                		   url = path;
                    	   url += validQuery[m];
                    	   System.out.println(url + " : " + testUrl.isValid(url));

                       }
                   }
               }
           }
       }
   }  
}
