

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
//You can use this function to implement your manual testing	   
	   UrlValidator url = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println(url.isValid("http://www.neopets.com"));
   }
   
   
   public void testScheme()
   {
	   String url = "www.neopets.com";
	   UrlValidator testUrl = new UrlValidator();
	   
	   String[] validScheme = {"http://", "ftp://", "h3t://", "https://", "ftp://", ""};
       String[] invalidScheme = {"3ht://", "http:/", "http:", "http/", "://"};
       System.out.println("Partition Testing: Scheme");
       System.out.println("Valid Schemes");
       for (int x = 0; x < validScheme.length; x++) {
    	   System.out.println(validScheme[x] + url + ": " + testUrl.isValid(validScheme[x] + url));
       }
       System.out.println("Invalid Schemes");
       for (int x = 0; x < invalidScheme.length; x++) {
    	   System.out.println(invalidScheme[x] + url + ": " + testUrl.isValid(invalidScheme[x] + url));
       }
       
   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
