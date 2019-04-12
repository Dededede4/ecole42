let () =
let p = new Doctor.doctor ("mprevot") 0 (new People.people("lolpipole")) in p#talk ; print_endline p#to_string; p#travel_in_time 1993 2019 ; print_endline p#to_string; p#use_sonic_screwdriver