/// <reference path="jquery.min.js" />
var width=0;
var height=0;
var hard=0;
var flag=parseInt(0);
var a;
var snake_head;
var snake_tail;
var snake_body;
var snake_direction;
var on_going=0;
var start;
var direction;
var visit;
var all_blank;
var food_num;
var all_food_num=10;
var food=new Array(all_food_num);
food.fill(-1);

var show;
var key=new Array();

console.log(a);

function init_visit(visit,flag)
{
	visit=new Array();
	for(var i=0;i<=(height+1);i++)
	{
		visit[i]=new Array();
		for(var j=0;j<=(width+1);j++)
		{
			visit[i][j]=flag;
		}
	}
	return visit;
}
function pick_start_point()
{
	var flag=1;
	var i=0;
	flag=Math.floor(Math.random()*4);
	var j;
	var x,y;
	y=Math.floor(Math.random()*(width-4))+4;
	x=Math.floor(Math.random()*(height-4))+4;
	start_point={x:x,y:y,direction:flag};
	cur=start_point;
	return start_point;
}

function point_to_count(i,j)
{
	return (i-1)*(width)+j;
}
function get_food()
{
	var y=Math.floor(Math.random()*(width))+1;
	var x=Math.floor(Math.random()*(height))+1;
	//console.log(width,height,x,y);
	while((snake_body.findIndex(n=>n==point_to_count(x,y))!=-1)&&on_going==1)
	{
		y=Math.floor(Math.random()*(width))+1;
		x=Math.floor(Math.random()*(height))+1;
	}
	return {x:x,y:y};
}
function show_place(num,type="normal")
{	
	if(type=="food")
	{
		$(`input[id=${num}]`).addClass("food");
		$(`input[id=${num}]`).removeClass("default");
	}
	else if(type=="get_food")
	{
		$(`input[id=${num}]`).removeClass("food");
		$(`input[id=${num}]`).addClass("walk");
	}
	else
	{
		$(`input[id=${num}]`).addClass("walk");
		$(`input[id=${num}]`).removeClass("default");
	}
}
function back_place(num,type="normal")
{
	if(type=="food")
	{
		$(`input[id=${num}]`).removeClass("food");
		$(`input[id=${num}]`).addClass("default");
	}
	else
	{
		$(`input[id=${num}]`).removeClass("walk");
		$(`input[id=${num}]`).addClass("default");
	}

}
function key_event()
{
	var p;
	var x=[-1,0,1,0];
	var y=[0,1,0,-1];

	console.log(snake_body);
	show = setInterval(function(){
			console.log('pp');
			if(food_num<all_food_num)
			{
				var flag=-1;
				for(var i=0;i<food_num;i++)
				{
					if(food[i]==-1)
					{
						flag=i;
						break;
					}
				}
				var new_food=get_food();
				food.splice(flag,1,new_food);

				console.log("ne_food");
				console.log(new_food.x,new_food.y,point_to_count(new_food.x,new_food.y),visit[new_food.x][new_food.y]);
				console.log(visit[new_food.x]);
				for(var j=1;j<13;j++)
					console.log(visit[j]);
				visit[new_food.x][new_food.y]=1;
				show_place(point_to_count(new_food.x,new_food.y),"food");
				food_num++;
			}
			var new_x,new_y;
			new_x=snake_head.x+x[snake_direction];
			new_y=snake_head.y+y[snake_direction];
			if(new_x<1||new_x>height||new_y<1||new_y>width)
			{
				alert("you  lose!!");
				clearInterval(show);
				re_start();
				
			}
			else
			{
				console.log("visit: ",visit[new_x][new_y]);
				if(snake_body.findIndex(x=>x==point_to_count(new_x,new_y))!=-1)
				{
					alert("lose");
					clearInterval(show);
					re_start();
				}
				else
				{
					console.log("vist : new direction: ",new_x,new_y,visit[new_x][new_y]);
					var flag=-1;
					for(var i=0;i<all_food_num;i++)
					{
						if(food[i]!=-1)
						{
							console.log("food",food[i]);
							if(food[i].x==new_x&&food[i].y==new_y)
							{
								flag=i;
								break;
							}
						}					
					}
					if(flag!=-1)
					{
						food.splice(flag,1,-1);
						console.log("all_blank: ",all_blank);
						snake_body.push(point_to_count(new_x,new_y));
						snake_head={x:new_x,y:new_y};
						show_place(point_to_count(snake_head.x,snake_head.y),"get_food");
						visit[snake_head.x][snake_head.y]=2;
						console.log("get_food");
						console.log("visit: ",new_x,new_y,visit[new_x][new_y]);
						food_num--;
						all_blank--;
					}
					else
					{				
						snake_body.push(point_to_count(new_x,new_y));
						snake_head={x:new_x,y:new_y};
						var xx,yy;

						console.log("back_place");
						visit[new_x][new_y]=2;
						//onsole.log("00000",snake_tail.x,snake_tail.y,visit[snake_tail.x][snake_tail.y]);
						snake_tail=snake_body.shift();
						console.log(snake_tail);
						xx=Math.floor((snake_tail-1)/width)+1;
						yy=snake_tail-width*(xx-1);
						console.log("xx,yy",xx,yy);
						
						//console.log("visit: ",new_x,new_y,visit[new_x][new_y]);
						show_place(point_to_count(snake_head.x,snake_head.y));
						back_place(snake_tail);
						//console.log("00000",snake_tail.x,snake_tail.y,visit[snake_tail.x][snake_tail.y]);
						visit[xx][yy]=0;
						//console.log("00000",snake_tail.x,snake_tail.y,visit[snake_tail.x][snake_tail.y]);
					}
						for(var j=1;j<13;j++)
					console.log(visit[j]);
					
				}
			}
		}, 400*(all_blank/(height*width)));
		document.onkeydown=function(event){
		 	var e = event || window.event || arguments.callee.caller.arguments[0];
            if(e)
            {
				visit=init_visit(visit,0);
				visit[start.x][start.y]=1;
				//var key=[37,39];
				
				
				var weight=[-1,1];
            	console.log(e.keyCode);
             	for(var i=0;i<key.length;i++)
             	{
	         		if(e.keyCode==key[i])
	         		{  
	         			if(hard==1)
	         			{
	         				snake_direction=(weight[i]+snake_direction+4)%4;
	         			}
	         			else
		         		{
		         			snake_direction=i;
		         		}
	         			console.log("snake_direction: ",snake_direction);
	         			return false;
	         			break;
	         		}
	         	}
	         	console.log(e.keyCode);
	         }
		};
}

function make_matrix(w,h)
{
	var text='';
	var class_type;
	var count=0;
	height=h;
	width=w;

	visit=init_visit(visit,0);
	console.log(visit);
	console.log(height+1,width+2);
	all_blank=height*width-1;
	start=pick_start_point();
	direction=start.direction;
	snake_direction=start.direction;
	snake_head={x:start.x,y:start.y};
	snake_tail={x:start.x,y:start.y};
	snake_body=new Array();
	snake_body.push(point_to_count(snake_head.x,snake_head.y));
	visit[start.x][start.y]=2;
	console.log("start",visit,start.x,start.y);
	console.log(start);
	class_type="default";
	for(var i=1;i<=height;i++)
	{
		for(var j=1;j<=width;j++)
		{
			//class_type= d[i][j]==0?"default":"block";
			count++;
			text+=`<input type="button" class="${class_type}" value=""  name="${count}" id="${count}" onmousedown="check_bomb(this.id)">`;
		}
		text+=`</br>`;
	}
	//console.log(text);
	$('#bg').append(text);
	$(`input[id=${point_to_count(start.x,start.y)}]`).removeClass("default");

	$(`input[id=${point_to_count(start.x,start.y)}]`).addClass("walk");
	$('#re_start').show();
	// $('#help').show();
	$('#ask_height_width').hide();
}
function start_game()
{
	if(on_going==0)
	{
			on_going=1;
			food_num=0;
			console.log(visit);
			var h=$('#height').val();
			var w=$('#width').val();

			hard=parseInt($('#hard').val());
			if(hard==0)
			{
				key=[38,39,40,37];
			}
			else
			{
				key=[37,39];
			}
			console.log(h,w);
			w=parseInt(w);
			h=parseInt(h);
			console.log(w+1,h+2);
			make_matrix(w,h);
			key_event();
	}
}
function re_start()
{
	width=0;
	height=0;
	hard=0;
	flag=parseInt(0);
	snake_head='';
	snake_tail='';
	snake_body=new Array();
	snake_direction=0;
	on_going=0;
	start=0;
	direction=0;
	visit=new Array();
	all_blank=0;
	food_num=0;
	food=new Array(all_food_num);
	food.fill(-1);
	flag=0;
	on_going=0;
	$('#bg').empty();
	
	clearInterval(show);
	$('#re_start').hide();
	$('#ask_height_width').show();
	
}