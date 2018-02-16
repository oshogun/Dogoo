import libtcodpy as libtcod
 
#actual size of the window
SCREEN_WIDTH = 80
SCREEN_HEIGHT = 50
 
MAP_WIDTH = 80
MAP_HEIGHT = 45

ROOM_MAX_SIZE = 10 
ROOM_MIN_SIZE = 6
MAX_ROOMS = 30

MAX_ROOM_MONSTERS = 3

FOV_ALGO = 0
FOV_LIGHT_WALLS = True
TORCH_RADIUS = 10 

LIMIT_FPS = 60  #60 frames-per-second maximum


class Rect:
    def __init__(self, x, y, w, h):
        self.x1 = x;
        self.y1 = y;
        self.x2 = x + w;
        self.y2 = y + h;

    def center(self):
        center_x = (self.x1 + self.x2) / 2
        center_y = (self.y1 + self.y2) / 2
        return (center_x, center_y)

    def intersect(self, other):
        return (self.x1 <= other.x2 and self.x2 >= other.x1 and 
                self.y1 <= other.y2 and self.y2 >= other.y1)

class Tile:
    def __init__(self, blocked, block_sight = None):
        self.explored = False
        self.blocked = blocked

        if block_sight is None: block_sight = blocked
        self.block_sight = block_sight

class Object:

    def __init__(self, x, y, char, name, color, blocks=False):
        self.x = x;
        self.y = y;
        self.char = char
        self.color = color
        self.name = name 
        self.blocks = blocks 

    def move(self, dx, dy):
        if self.x + dx >= 0 and self.y + dy >= 0 and self.x + dx < MAP_WIDTH and self.y + dy < MAP_HEIGHT:
            if not is_blocked(self.x + dx, self.y + dy):
                self.x += dx
                self.y += dy 

    def draw(self):
        if libtcod.map_is_in_fov(fov_map, self.x, self.y):
            libtcod.console_set_default_foreground(con, self.color)
            libtcod.console_put_char(con, self.x, self.y, self.char, libtcod.BKGND_NONE)

    def clear(self):
        libtcod.console_put_char(con, self.x, self.y, ' ', libtcod.BKGND_NONE) 

    

def create_room(room):
    global map

    for x in range(room.x1 + 1, room.x2):
        for y in range(room.y1 + 1, room.y2):
            map[x][y].blocked = False 
            map[x][y].block_sight = False  

def handle_keys():
    global fov_recompute
 
    #key = libtcod.console_check_for_keypress()  #real-time
    key = libtcod.console_wait_for_keypress(True)  #turn-based
 
    if key.vk == libtcod.KEY_ENTER and key.lalt:
        #Alt+Enter: toggle fullscreen
        libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())
 
    elif key.vk == libtcod.KEY_ESCAPE:
        return 'exit'  #exit game
 
    #movement keys

    if game_state == 'playing':
        if libtcod.console_is_key_pressed(libtcod.KEY_UP):
            player_move_or_attack(0, -1)
            fov_recompute = True
     
        elif libtcod.console_is_key_pressed(libtcod.KEY_DOWN):
            player_move_or_attack(0, 1)
            fov_recompute = True
                
        elif libtcod.console_is_key_pressed(libtcod.KEY_LEFT):
            player_move_or_attack(-1, 0)
            fov_recompute = True
        
        elif libtcod.console_is_key_pressed(libtcod.KEY_RIGHT):
            player_move_or_attack(1, 0)
            fov_recompute = True
        else:
            return 'skip-turn'
 
def make_map():
    global map 

    map = [[ Tile(True)
        for y in range(MAP_HEIGHT)]
            for x in range(MAP_WIDTH)]

    rooms = []
    num_rooms = 0

    for r in range(MAX_ROOMS):
        #random width and height
        w = libtcod.random_get_int(0, ROOM_MIN_SIZE, ROOM_MAX_SIZE)
        h = libtcod.random_get_int(0, ROOM_MIN_SIZE, ROOM_MAX_SIZE)

        #random pos inside map
        x = libtcod.random_get_int(0, 0, MAP_WIDTH - w - 1)
        y = libtcod.random_get_int(0, 0, MAP_HEIGHT - h - 1)

        new_room = Rect(x, y, w, h)

        #check intersection
        failed = False 
        for other_room in rooms:
            if new_room.intersect(other_room):
                failed = True 
                break 
        if not failed: 
            create_room(new_room)
            (new_x, new_y) = new_room.center()

            if num_rooms == 0:
                #starting position of player 
                player.x = new_x
                player.y = new_y
            else:
                (prev_x, prev_y) = rooms[num_rooms - 1].center()

                if libtcod.random_get_int(0, 0, 1) == 1:
                    create_h_tunnel(prev_x, new_x, prev_y)
                    create_v_tunnel(prev_y, new_y, new_x)
                else:
                    create_v_tunnel(prev_y, new_y, prev_x)
                    create_h_tunnel(prev_x, new_x, new_y)
            place_objects(new_room)
            rooms.append(new_room)
            num_rooms +=1
def create_h_tunnel(x1, x2, y):
    global map 
    for x in range(min(x1, x2), max(x1, x2) + 1):
        map[x][y].blocked = False
        map[x][y].block_sight = False

def create_v_tunnel(y1, y2, x):
    global map 
    for y in range(min(y1,y2), max(y1,y2) + 1):
        map[x][y].blocked = False
        map[x][y].block_sight = False


def place_objects(room):
    num_monsters = libtcod.random_get_int(0,0, MAX_ROOM_MONSTERS)

    for i in range(num_monsters):
        x = libtcod.random_get_int(0, room.x1, room.x2)
        y = libtcod.random_get_int(0, room.y1, room.y2)
        if not is_blocked(x, y):
            if libtcod.random_get_int(0, 0, 100) < 80: # 80% chance of spawning a Sentinel
                # spawn a Sentinel
                monster = Object(x, y, 's', 'Snek', libtcod.desaturated_green, blocks=True)
            else:
                # spawn a Lurker
                monster = Object(x,y, 'L', 'Lurker', libtcod.darker_green, blocks=True)
            objects.append(monster)

def is_blocked(x, y):
        if map[x][y].blocked:
            return True 

        for object in objects:
            if object.blocks and object.x == x and object.y == y:
                return True 
        return False 

def render_all():
    global color_light_wall
    global color_light_ground
    global color_dark_wall
    global color_light_ground
    global fov_recompute
    global fov_map 

    if fov_recompute:
        fov_recompute = False 
        libtcod.map_compute_fov(fov_map, player.x,player.y, TORCH_RADIUS, FOV_LIGHT_WALLS, FOV_ALGO)

    #go through all tiles, and set their background color according to the FOV
    for y in range(MAP_HEIGHT):
        for x in range(MAP_WIDTH):
            visible = libtcod.map_is_in_fov(fov_map, x, y)
            wall = map[x][y].block_sight

            if not visible:
                if map[x][y].explored:
                    if wall:
                        libtcod.console_set_char_background(con, x, y, color_dark_wall, libtcod.BKGND_SET)
                    else:
                        libtcod.console_set_char_background(con, x, y, color_dark_ground, libtcod.BKGND_SET)
            else:
                if wall:
                    libtcod.console_set_char_background(con, x, y, color_light_wall, libtcod.BKGND_SET)
                else:
                    libtcod.console_set_char_background(con, x, y, color_light_ground, libtcod.BKGND_SET)
                map[x][y].explored = True
    #draw all objects in the list
    for object in objects:
        object.draw()
 
    #blit the contents of "con" to the root console
    libtcod.console_blit(con, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0)

def player_move_or_attack(dx, dy):
    global fov_recompute
 
    #the coordinates the player is moving to/attacking
    x = player.x + dx
    y = player.y + dy
 
    #try to find an attackable object there
    target = None
    for object in objects:
        if object.x == x and object.y == y:
            target = object
            break
 
    #attack if target found, move otherwise
    if target is not None:
        print 'You are too pathetically weak, and cause ' + target.name + ' no harm. There\'s only despair left for you.'
    else:
        player.move(dx, dy)
        fov_recompute = True

############################################################################################################
#                                         Initialization & Main Loop                                       #
############################################################################################################
 
libtcod.console_set_custom_font('arial10x10.png', libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(SCREEN_WIDTH, SCREEN_HEIGHT, 'Dogoo: A conscience crisis', False)
con = libtcod.console_new(SCREEN_WIDTH, SCREEN_HEIGHT)
libtcod.sys_set_fps(LIMIT_FPS)
 
player = Object(0, 0, '@', 'player', libtcod.white, blocks=True)

color_dark_wall = libtcod.Color(0, 0, 100)
color_light_wall = libtcod.Color(130, 110, 50)
color_dark_ground = libtcod.Color(50, 50, 150)
color_light_ground = libtcod.Color(200, 180, 50)

game_state = 'playing'
player_action = None 

objects = [player]

make_map()

fov_map = libtcod.map_new(MAP_WIDTH, MAP_HEIGHT)
for y in range(MAP_HEIGHT):
    for x in range(MAP_WIDTH):
        libtcod.map_set_properties(fov_map, x, y, not map[x][y].block_sight, not map[x][y].blocked)

fov_recompute = True 
while not libtcod.console_is_window_closed():
 
    render_all()

    libtcod.console_flush()

    for object in objects:
        object.clear()

    #handle keys and exit game if needed
    player_action = handle_keys()
    if player_action == 'exit':
        break
    if game_state == 'playing' and player_action != 'skip-turn':
        for object in objects:
            if object != player:
                print '' + object.name +' waits.'