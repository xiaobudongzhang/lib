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
        file_get_contents("{$this->base_url}/index.html");
		 file_put_contents('E:/libcookie', json_encode($_COOKIE).PHP_EOL,FILE_APPEND);
        $this->assertEquals('value', $cookies->get('name222111'));
	}
}