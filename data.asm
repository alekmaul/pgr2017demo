.include "hdr.asm"

.section ".rogener1" superfree

fontg: .incbin "gfxs/fonts.pic"
fontg_end:
fontp: .incbin "gfxs/fonts.pal"

starsg: .incbin "gfxs/stars.pic"
starsg_end:
starsp: .incbin "gfxs/stars.pal"
starsm: .incbin "gfxs/stars.map"

logog: .incbin "gfxs/logo.pic"
logog_end:
logop: .incbin "gfxs/logo.pal"
logom: .incbin "gfxs/logo.map"

spriteg: .incbin "gfxs/sprites.pic"
spriteg_end:
spritep: .incbin "gfxs/sprites.pal"

.ends

.section ".rogener2" superfree

firstonesg: .incbin "gfxs/firstone.pic"
firstonesg_end:

firstonesp: .incbin "gfxs/firstone.pal"
firstonesm: .incbin "gfxs/firstone.map"

lastonesp: .incbin "gfxs/lastone.pal"
lastonesm: .incbin "gfxs/lastone.map"

.ends

.section ".rogener3" superfree

lastonesg: .incbin "gfxs/lastone.pic"
lastonesg_end:

.ends

; --------------------------  Sound + Music
.bank 5
.section "SOUNDBANK0" ; need dedicated bank(s)

__SOUNDBANK__0:
;.incbin "soundbank.bnk" read $8000
.incbin "soundbank.bnk" 
.ends

;.bank 6
;.section "SOUNDBANK1" ; need dedicated bank(s)

;__SOUNDBANK__1:
;.incbin "soundbank.bnk" skip $8000
;.ends

