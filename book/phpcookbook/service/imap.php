<?php
$fh=imap_open('{pop.163.com:110/pop3}','18949424439@163.com','ha123o');
if(!$fh){
	return $fh;
}
//$headers = imap_headers($fh);

$last=imap_num_msg($fh);
$header=imap_header($fh,$last);

$body=imap_body($fh,$last);

$tran_body=imap_qprint($body);
//支持结构  html  plain
$palin_text=imap_fetchstructure($fh,$last);

/* if(!empty($palin_text->parts)){
	foreach ($palin_text->parts as $key=>$value) {
		if($value->subtype=='PLAIN'){
			print_r(imap_fetch$expression)
		}
		;
	}
} */
//获取存文本
$x=imap_fetchbody($fh,$last,2);
print_r(imap_qprint($x));
//print_r($palin_text);
//print_r(imap_qprint($body));
imap_close($fh);