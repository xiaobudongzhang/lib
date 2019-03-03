<?php
class Calendar {
	protected $monthToUse;
	protected $prepared = false;
	protected $days = array ();
	public function __construct($month, $year) {
		$month=$month?:date('m');
		$year=$year?:date('Y');
		$this->monthToUse = DateTime::createFromFormat ( 'Y-m|', sprintf ( "%04d-%02d", $year, $month ) );
		//print_r($this->monthToUse);
		$this->prepare ();
		// print_r ( $this->days );
	}
	protected function prepare() {
		foreach ( array (
				'Su',
				'Mo',
				'Tu',
				'We',
				'Th',
				'Fr',
				'Sa' 
		) as $dow ) {
			$endOfRow = ($dow == 'Sa');
			$this->days [] = array (
					'type' => 'dow',
					'label' => $dow,
					'endOfRow' => $endOfRow 
			);
		}
		// 星期中的第几天 0（表示星期天）到 6（表示星期六）
		for($i = 0, $j = $this->monthToUse->format ( 'w' ); $i < $j; $i ++) {
			$this->days [] = [ 
					'type' => 'blank' 
			];
		}
		
		$today = date ( 'Y-m-d' );
		// 给定月份所应有的天数 28 到 31
		$days = new DatePeriod ( $this->monthToUse, new DateInterval ( 'P1D' ), $this->monthToUse->format ( 't' ) - 1 );
		foreach ( $days as $day ) {
			$isToday = ($day->format ( 'Y-m-d' ) == $today);
			$endOfRow = ($day->format ( 'w' ) == 6);
			$this->days [] = array (
					'type' => 'day',
					'label' => $day->format ( 'j' ),
					'today' => $isToday,
					'endOfRow' => $endOfRow 
			);
		}
		if (! $endOfRow) {
			for($i = 0, $j = 6 - $day->format ( 'w' ); $i < $j; $i ++) {
				$this->days [] = array (
						'type' => 'blank' 
				);
			}
		}
	}
	// output html
	public function html($opts = []) {
		if (! isset ( $opts ['id'] )) {
			$opts ['id'] = 'calendar';
		}
		if (! isset ( $opts ['month_link'] )) {
			$opts ['month_link'] = '<a href="' . htmlentities ( $_SERVER ['PHP_SELF'] ) . '?' . 'month=%d&amp;year=%d">%s</a>';
		}
		$classes = [ ];
		foreach ( array (
				'prev',
				'month',
				'next',
				'weekday',
				'blank',
				'day',
				'today' 
		) as $classe ) {
			if (isset ( $opts ['class'] ) && isset ( $opts ['class'] [$classe] )) {
				$classes [$classe] = $opts ['class'] [$classe];
			} else {
				$classes [$classe] = $classe;
			}
		}
	}
		// output cmd
	function text() {
		$lineLength = strlen ( 'Su Mo Tu We Th Fr Sa' );
		$header = $this->monthToUse->format ( 'F Y' );
		$headerSpacing = floor ( ($lineLength - strlen ( $header )) / 2 );
		
		$text = str_repeat ( ' ', $headerSpacing ) . $header . PHP_EOL;
		foreach ( $this->days as $i => $day ) {
			switch ($day ['type']) {
				case 'dow' :
					$text .= sprintf ( '%2s', $day ['label'] );
					break;
				case 'blank' :
					$text .= '  ';
					break;
				case 'day' :
					$text .= sprintf ( '%2d', $day ['label'] );
					break;
				default :
					;
					break;
			}
			$text.=(isset($day['endOfRow'])&&$day['endOfRow'])?PHP_EOL:' ';
		}
		if($text[strlen($text)-1]!=PHP_EOL){
			$text.=PHP_EOL;
		}
	
		return $text;
	}
	
}

if(php_sapi_name()=='cli'){
	$ca = new Calendar ( isset($argv[2])?$argv[2]:'', isset($argv[1])?$argv[1]:'' );
	echo $ca->text();
}else{
	$ca = new Calendar (6, 2016 );
}
