var c = document.getElementById("myCanvas");
var ctx = c.getContext("2d");
ctx.canvas.width  = window.innerWidth;
ctx.canvas.height = window.innerHeight;

var ip = prompt("Please enter Ip and Port", "10.13.253.209:1234");
var socket = io.connect('http://127.0.0.1:1337');

var grass = new Image();
var bois = new Image();
var chaudron = new Image();
var minerai = new Image();
var nourriture = new Image();
var rubi = new Image();
var sable = new Image();
var saphir = new Image();

var inc = new Image();

var broad = new Image();

var down1 = new Image();
var up1 = new Image();
var right1 = new Image();
var left1 = new Image();

var down2 = new Image();
var up2 = new Image();
var right2 = new Image();
var left2 = new Image();

var down3 = new Image();
var up3 = new Image();
var right3 = new Image();
var left3 = new Image();

var down4 = new Image();
var up4 = new Image();
var right4 = new Image();
var left4 = new Image();

var down5 = new Image();
var up5 = new Image();
var right5 = new Image();
var left5 = new Image();

var down6 = new Image();
var up6 = new Image();
var right6 = new Image();
var left6 = new Image();

grass.src = 'asset/grass.jpg';
bois.src = 'asset/bois.png';
chaudron.src = 'asset/chaudron.png';
minerai.src = 'asset/minerai.png';
nourriture.src = 'asset/nourriture.png';
rubi.src = 'asset/rubi.png';
sable.src = 'asset/sable.png';
saphir.src = 'asset/saphir.png';

inc.src = 'asset/incante.png';
broad.src = 'asset/broadcast.png';

down1.src = 'asset/d/d_down.png';
up1.src = 'asset/d/d_up.png';
right1.src = 'asset/d/d_right.png';
left1.src = 'asset/d/d_left.png';

down2.src = 'asset/d/d_down2.png';
up2.src = 'asset/d/d_up2.png';
right2.src = 'asset/d/d_right2.png';
left2.src = 'asset/d/d_left2.png';

down3.src = 'asset/d/d_down3.png';
up3.src = 'asset/d/d_up3.png';
right3.src = 'asset/d/d_right3.png';
left3.src = 'asset/d/d_left3.png';

down4.src = 'asset/d/d_down4.png';
up4.src = 'asset/d/d_up4.png';
right4.src = 'asset/d/d_right4.png';
left4.src = 'asset/d/d_left4.png';

down5.src = 'asset/d/d_down5.png';
up5.src = 'asset/d/d_up5.png';
right5.src = 'asset/d/d_right5.png';
left5.src = 'asset/d/d_left5.png';

down6.src = 'asset/d/d_down6.png';
up6.src = 'asset/d/d_up6.png';
right6.src = 'asset/d/d_right6.png';
left6.src = 'asset/d/d_left6.png';

var down = new Array();
var up = new Array();
var right = new Array();
var left = new Array();

down.push(down1);
up.push(up1);
right.push(right1);
left.push(left1);

down.push(down2);
up.push(up2);
right.push(right2);
left.push(left2);

down.push(down3);
up.push(up3);
right.push(right3);
left.push(left3);

down.push(down4);
up.push(up4);
right.push(right4);
left.push(left4);

down.push(down5);
up.push(up5);
right.push(right5);
left.push(left5);

down.push(down6);
up.push(up6);
right.push(right6);
left.push(left6);

socket.on('connect', function(packet){Handle_connect(packet)});
socket.on('data', function(packet){Handle_update(packet)});
socket.on('errors', function(packet){Handle_error(packet)});

var map_x = 0;
var map_y = 0;
var content = new Array();
var player = new Array();

$(window).load(function(){
    setInterval(function(){ draw(); }, 50);
	console.log("ready");
});

function Handle_connect(packet)
{
	socket.emit('start', { ip: ip.split(":")[0], port: ip.split(":")[1]});
}

window.addEventListener("resize", function () {
	ctx.canvas.width  = window.innerWidth;
	ctx.canvas.height = window.innerHeight;
});

function Handle_error(packet)
{
	alert(packet);
}

function Handle_update(p)
{
	if (p == null)
		return;
	if (p == "BIENVENUE")
		return;
	var line = p.split("\n");
	var i = 0;
	while (i != line.length)
	{
		var packet = line[i]; 
		if (packet.indexOf(" ") != -1)
		{
			console.log("/*" + packet + "*/");
			if (packet.split(" ")[0] == "msz")
				Create_Map(packet);
			if (packet.split(" ")[0] == "bct")
				Store_res(packet);
			if (packet.split(" ")[0] == "pnw")
				Create_Player(packet);
			if (packet.split(" ")[0] == "ppo")
				Move_Player(packet);
			if (packet.split(" ")[0] == "pic")
				Start_incante(packet);
			if (packet.split(" ")[0] == "pie")
				Stop_incante(packet);
			/*if (cmd.split(" ")[0].equals("pdr"))
				Take(cmd);
			if (cmd.split(" ")[0].equals("pgt"))
				Take(cmd);*/
			if (packet.split(" ")[0] == "pdi")
				Dead(packet);
			if (packet.split(" ")[0] == "pbc")
				Broad(packet);
			if (packet.split(" ")[0] == "plv")
				Change_level(packet);
		}
		i++;
	}
}

function browserSize()
{
	return { x: window.innerWidth, y: window.innerHeight };
}

function Dead(cmd)
{
	player.splice(parseInt(cmd.split(" ")[1]), 1);
}

function Change_level(cmd)
{
	var id = find_player(parseInt(cmd.split(" ")[1]));
	var l = parseInt(cmd.split(" ")[2]);
	console.log("Changement de niveau : " + id + " : " + l);
	player[id].level = l;
}

function Broad(cmd)
{
	var id = parseInt(cmd.split(" ")[1]);
	player[find_player(id)].time = new Date().getMilliseconds();
	player[find_player(id)].ptime = player[find_player(id)].time;
	player[find_player(id)].broad_state = true;
}

function Start_incante(cmd)
{
	var i = 4;
	while (i < cmd.split(" ").length)
	{
		player[find_player(parseInt(cmd.split(" ")[i]))].state_inc = true;
		i++;
	}
}

function Stop_incante(cmd)
{
	var x = parseInt(cmd.split(" ")[1]);
	var y = parseInt(cmd.split(" ")[2]);
	var i = 0;
	while (i < find_player_by_xy(x,y).length)
	{
		player[find_player_by_xy(x,y)[i]].state_inc = false;
		i++;
	}
}

function Move_Player(cmd)
{
	var id = parseInt(cmd.split(" ")[1]);
	var x = parseInt(cmd.split(" ")[2]);
	var y = parseInt(cmd.split(" ")[3]);
	var o = parseInt(cmd.split(" ")[4]);
	player[find_player(id)].x = x;
	player[find_player(id)].y = y;
	player[find_player(id)].o = o;
}

function Create_Player(cmd)
{
	console.log("create_player");
	var id = parseInt(cmd.split(" ")[1]);
	var x = parseInt(cmd.split(" ")[2]);
	var y = parseInt(cmd.split(" ")[3]);
	var o = parseInt(cmd.split(" ")[4]);
	var l = parseInt(cmd.split(" ")[5]);
	player.push({"id":id, "x":x,"y":y,"o":o,"level":l,"state_inc":false,"time":0,"ptime":0,"broad_state":false});
}

function Store_res(cmd)
{
	var x = parseInt(cmd.split(" ")[1]);
	var y = parseInt(cmd.split(" ")[2]);
	var a = parseInt(cmd.split(" ")[3]);
	var b = parseInt(cmd.split(" ")[4]);
	var c = parseInt(cmd.split(" ")[5]);
	var d = parseInt(cmd.split(" ")[6]);
	var e = parseInt(cmd.split(" ")[7]);
	var f = parseInt(cmd.split(" ")[8]);
	var g = parseInt(cmd.split(" ")[9]);
	content[x][y][0] = a;
	content[x][y][1] = b;
	content[x][y][2] = c;
	content[x][y][3] = d;
	content[x][y][4] = e;
	content[x][y][5] = f;
	content[x][y][6] = g;
}

function Create_Map(cmd)
{
	console.log("create_map");
	var x = parseInt(cmd.split(" ")[1]);
	var y = parseInt(cmd.split(" ")[2]);
	
	map_x = x;
	map_y = y;
	
	var i = 0;
	var j = 0;
	var e = 0;
	
	while (i != x)
	{
		j = 0;
		content[i] = new Array();
		while (j != y)
		{
			e = 0;
			content[i][j] = new Array();
			while (e != 7)
			{
				content[i][j][e] = 0;
				e++;
			}
			j++;
		}
		i++;
	}
}

function draw()
{
	ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
	draw_map();
	draw_res();
	draw_player();
}

function draw_player()
{
	var casew = (browserSize().x / map_x);
	var caseh = (browserSize().y / map_y);
	var current;
	for (var i in player)
	{
		if (player[i].o == 1)
			current = down[player[i].level - 1];
		else if (player[i].o == 2)
			current = right[player[i].level - 1];
		else if (player[i].o == 3)
			current = up[player[i].level - 1];
		else if (player[i].o == 4)
			current = left[player[i].level - 1];
		var tmp_y = player[i].y;
		player[i].y = map_y - player[i].y;
		player[i].y--;
		if (player[i].state_inc == true)
			ctx.drawImage(inc, player[i].x * casew, player[i].y * caseh, casew, caseh);
		ctx.drawImage(current, (player[i].x * casew) + casew / 4, (player[i].y * caseh) + caseh / 4, casew / 2, caseh / 2);
		if (player[i].broad_state == true)
		{
			if (player[i].time - player[i].ptime > 500)
				player[i].broad_state = false;
			ctx.drawImage(broad, player[i].x * casew + casew / 4, player[i].y * caseh, casew / 2, caseh / 2);
			player[i].time = new Date().getMilliseconds();
		}
		player[i].y = tmp_y;
	}
}

function draw_res()
{
	var i = 0;
	var j = 0;
	var e = 0;
	
	while (i != map_x)
	{
		j = 0;
		while (j != map_y)
		{
			e = 0;
			while (e != 7)
			{
				if (content[i][j][e] > 0)
					draw_sprite_res(e, i, j);
				e++;
			}
			j++;
		}
		i++;
	}
}

function draw_sprite_res(e, x, y)
{
	var grassw = (browserSize().x / map_x);
	var boisw = grassw / 7;
	var grassh = (browserSize().y / map_y);
	var boish = grassh / 7;
	y = map_y - y;
	y--;
	
	if (e == 0)
		ctx.drawImage(bois,((x) * grassw) + boisw / 2, y * grassh + boish / 2, boisw, boish);
	else if (e == 1)
		ctx.drawImage(chaudron,((x) * grassw) + boisw / 2, (y * grassh) + grassh - boish * 1.5, boisw, boish);
	else if (e == 2)
		ctx.drawImage(minerai,((x) * grassw) + boisw * 5, y * grassh + boish / 2, boisw, boish);
	else if (e == 3)
		ctx.drawImage(nourriture,((x) * grassw) + boisw * 3, y * grassh + boish / 2, boisw, boish);
	else if (e == 4)
		ctx.drawImage(rubi,((x) * grassw) + boisw * 3, y * grassh + boish * 2.5, boisw, boish);
	else if (e == 5)
		ctx.drawImage(sable,((x) * grassw) + boisw * 3, (y * grassh) + grassh - boish * 1.5, boisw, boish);
	else if (e == 6)
		ctx.drawImage(saphir,((x) * grassw) + boisw * 5, (y * grassh) + grassh - boish * 1.5, boisw, boish);
}

function draw_map()
{
	var i = 0;
	while (i != map_x)
	{
		var j = 0;
		while (j != map_y)
		{
			ctx.drawImage(grass, i * (browserSize().x / map_x), j * (browserSize().y / map_y), (browserSize().x / map_x), (browserSize().y / map_y));
			j++;
		}
		i++;
	}
}

function find_player(id)
{
  for (var i in player)
  {
    if (player[i].id == id)
      return (i);
  }
  return (-1);
}

function find_player_by_xy(x,y)
{
	var pl = new Array();
	for (var i in player)
	{
		if (player[i].x == x && player[i].y == y)
			pl.push(i);
	}
	return (pl);
}