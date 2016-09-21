<?php
include "vendor/autoload.php";
class meTest extends \PHPUnit_Extensions_Selenium2TestCase {

	private $base_url="http://www.local.com:81/";

	protected function setUp() {

	
		$this->setBrowser ( 'chrome' );
		$this->setBrowserUrl ( $this->base_url );
	}
	
	public function testAppointInfo(){

	    $this->url("{$this->base_url}/index.html");
	    

    $cookies = $this->cookie();
        $cookies->add('name222111', 'value')
      //->path('/')
      //  ->domain('127.0.0.1:8001')
        ->expiry(time()+60*60*24)
        ->secure(FALSE) 
        ->set(); 

        $this->assertEquals('value', 'value');
	}
}