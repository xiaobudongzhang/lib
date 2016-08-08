<?php
/**$feed = 'http://news.php.net/group.php?group=php.announce&format=rss';
require('rss_fetch.inc');
$rss = fetch_rss($feed);
print_r($rss);
**/
header('content-type:text/xml');
class rss2 extends DOMDocument{
      private $channel;
      
      public function __construct($title,$link,$des){
      parent::__construct();
      $this->formatOutput=true;

      $root=$this->appendChild($this->createElement('rss'));
      $root->setAttribute('version','2.0');
      
      $channel=$root->appendChild($this->createElement('channel'));
      $channel->appendChild($this->createElement('title',$title));
      $channel->appendChild($this->createElement('link',$link));
      $channel->appendChild($this->createElement('description',$des));

      $this->channel=$channel;
      
      }
      
      public function add($title,$link,$des){
      	     $item=$this->createElement('item');
	     $item->appendChild($this->createElement('title',$title));
	     $item->appendChild($this->createElement('link',$link));
	     $item->appendChild($this->createElement('description',$des));
	     $this->channel->appendChild($item);
      }

      
}

$rss = new rss2('Channel Title', 'http://www.example.org','Channel Description');
$rss->add('Item1','http://www.baidu.com','item1 des');
print $rss->saveXML();