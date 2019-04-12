class doctor name age sidekick =
  object
    val name:string = name
    val mutable age:int = age
    val sidekick:People.people = sidekick
    val mutable hp:int = 100

    method to_string = name ^ " have " ^ string_of_int (hp) ^ " hp " ^ string_of_int (age)
       ^ " age" ^ " and sidekick : " ^ sidekick#to_string

    method talk =  print_endline ("Hi! I’m the Doctor!")
    method travel_in_time start arrival = begin 
      age <- age + (arrival - start);
      print_endline "                 _.--._
                 _|__|_
     _____________|__|_____________
  .-'______________________________'-.
  | |________POLICE___BOX__________| |
  |  |============================|  |
  |  | .-----------..-----------. |  |
  |  | |  _  _  _  ||  _  _  _  | |  |
  |  | | | || || | || | || || | | |  |
  |  | | |_||_||_| || |_||_||_| | |  |
  |  | | | || || | || | || || | | |  |
  |  | | |_||_||_| || |_||_||_| | |  |
  |  | |  _______  ||  _______  | |  |
  |  | | |       | || |       | | |  |
  |  | | |       | || |       | | |  |
  |  | | |       | || |       | | |  |
  |  | | |_______| || |_______| | |  |
  |  | |  _______ @||@ _______  | |  |
  |  | | |       | || |       | | |  |
  |  | | |       | || |       | | |  |
  |  | | |       | || |       | | |  |
  |  | | |_______| || |_______| | |  |
  |  | |  _______  ||  _______  | |  |
  |  | | |       | || |       | | |  |
  |  | | |       | || |       | | |  |
  |  | | |       | || |       | | |  |
  |  | | |_______| || |_______| | |  |
  |  | '-----------''-----------' |  |
 _|__|/__________________________\\|__|_ 
'----'----------------------------'----'"

    end

    method use_sonic_screwdriver = print_endline "Whiiiiwhiiiwhiii Whiiiiwhiiiwhiii Whiiiiwhiiiwhiii"
  
    method private regenerate = hp <- 100

    initializer print_endline "(doctor) An initializer which indicate that the object has been created"
  end 