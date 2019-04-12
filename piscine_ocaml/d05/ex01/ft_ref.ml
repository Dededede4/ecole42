type 'a ft_ref = {mutable contents: 'a}

let return a = {contents = a}

let get a = a.contents

let set a b = a.contents := b

let bind a f = return (get (f (get a)))