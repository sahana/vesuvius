<script type="text/javascript">
	var chart;
	$(document).ready(function() {
	chart = new Highcharts.Chart({
		chart: {
			renderTo: 'container',
			defaultSeriesType: 'column'
				},
		title: {
			text: 'PL Status Statistics'
			},
		subtitle: {
			text: 'Source: Google Person Finder, Event: Christchurch Earthquake'
					},
		xAxis: {
			//categories: <?php echo json_encode($json_opt_status);?>, labels: {rotation: 0, align: 'left',
			categories: ['alive','deceased', 'found', 'missing', 'unknown'], labels: {rotation: 0, align: 'center',
			style: {
                    color: '#6D869F',
                    fontWeight: 'bold'
                  }	
				}
			},
		yAxis: {
			min: 0,
			title: {
				text: 'Total People count'
					}
				},
		legend: {
			layout: 'vertical',
			backgroundColor: '#FFFFFF',
			align: 'left',
			verticalAlign: 'top',
			x: 0,
			y: 50,
               },
		tooltip: {
			formatter: function() {
            return ''+
				this.x +': '+ this.y +'';
								}
				},
		plotOptions: {
			column: {
            pointPadding: 0.2,
            borderWidth: 0
					}
					},
        series: {
            events: {
                show: (function() {
                    var chart = this.chart,
                    series = chart.series,
                    i = series.length,
                    otherSeries;
                    while(i--) {
                        otherSeries = series[i];
                        if (otherSeries != this && otherSeries.visible) {
                            otherSeries.hide();
                              }
							}                        
						})
                   }
                }, 
		series: [{
			//name: 'Christchurch',                
			data:  [<?php echo join($count_opt_status, ', ');?>]		    
				}]  
			});  
	});
    });          
	</script>