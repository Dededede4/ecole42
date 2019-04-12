    module Card :
      sig
        module Color :
          sig
            type t = Spade | Heart | Diamond | Club
            val all : t list (** The list of all values of type t *)
            val toString : t -> string (** "S", "H", "D" or "C" *)
            val toStringVerbose : t -> string (** "Spade", "Heart", etc *)
          end
        module Value :
          sig
            type t = T2 | T3 | T4 | T5 | T6 | T7 | T8 | T9 | T10 | Jack | Queen | King | As
            (** The list of all values of type t *)
            val all : t list
            (** Interger representation of a card value, from 1 for T2 to 13 for As *)
            val toInt : t -> int
            (** returns "2", ..., "10", "J", "Q", "K" or "A" *)
            val toString : t -> string
            (** returns "2", ..., "10", "Jack", "Queen", "King" or "As" *)
            val toStringVerbose : t -> string
            (** Returns the next value, or calls invalid_arg if argument is As *)
            val next : t -> t
            (** Returns the previous value, or calls invalid_arg if argument is T2 *)
            val previous : t -> t
          end
        type t = Value.t * Color.t
        val newCard : Value.t -> Color.t -> t
        val allSpades : t list
        val allHearts : t list
        val allDiamonds : t list
        val allClubs : t list
        val all : t list
        val getValue : t -> Value.t
        val getColor : t -> Color.t
        val toString : t -> string
        val toStringVerbose : t -> string
        val compare : t -> t -> int
        val max : t -> t -> t
        val min : t -> t -> t
        val best : t list -> t
        val isOf : t -> Color.t -> bool
        val isSpade : t -> bool
        val isHeart : t -> bool
        val isDiamond : t -> bool
        val isClub : t -> bool
      end
    type t = Card.t list
    val newDeck : unit -> t
    val toStringList : t -> string
    val toStringListVerbose : t -> string
    val drawCard : t -> Card.t * t