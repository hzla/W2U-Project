# Pokémon icons: where each form's icon lives

The party / PC icons are archive `a/0/0/7` (`data/graphics/pokegra/icons`, files `07_<member>.bin`); each icon has
two members (the second empty unless a female icon exists). `src/pokedex_expansion/w2u_pokegra.cpp`
(`PokeParty_GetIconIndex`, `PokeParty_GetIconPalette`) picks them:

| Pokémon | Icon member | Palette map entry (`data/pml/pokeicon_palette_map.bin`) |
|---|---|---|
| species 1-721 | 8 + 2 * species | species |
| species 722-809 | 1904 + 2 * (species - 722) | species |
| species 810-1023 | 2408 + 2 * (species - 810) | species |
| a form (form > 0) | 1456 + 2 * (Form Sprite Offset + form - 1) | 724 + Form Sprite Offset + form - 1 |

The palette map holds one of the three shared icon palettes per entry (low nibble male, high nibble female).

## 2026-10-15: one scheme for every form

Until then the retail Megas (Mega Venusaur ... Mega Audino, Charizard / Mewtwo X and Y) used a second slot, 8 + 2 *
their personal index (and that palette entry). For personal indices 1024 and up that range is the form range itself,
so the Mega copies written there (`assets/pokeweb_pwan/form_icon_staging_report.json` `megaSpeciesIcons`) replaced
46 other forms' icons and palettes: Alolan Vulpix showed Mega Sceptile, Galarian Meowth Mega Sharpedo, and the Z-A
Megas, Floette's colours and female Meowstic showed other Megas. Now every form, Megas included, uses its form slot
(the direct path is gone), and the data was repaired (`w2u-local/pwan_fix/icon_plan.py`):

- retail Megas: their direct slot's icon and palette moved to their form slot (Mega Slowbro's form slot 2242 was
  missing and now exists);
- forms a Mega copy had replaced: their icon and palette from before the copies (5b9ffe56b~1);
- Megas that never had an icon of their own (the Z-A Megas, the Z Megas, Mega Floette, Mega Meowstic, Mega Magearna):
  their species' icon, until icons are drawn for them.

Checked in game (`w2u-local/checks/ui_checks.yml` UI_PC_ICONS): Galarian Meowth, Alolan Vulpix, Mega Charizard X,
yellow Floette, Mega Scolipede (Scolipede's icon) and Hisuian Growlithe in the PC.

When staging icons: write a form's icon to its form slot only. The direct slots of personal indices are not icon
slots any more.

## Minior and Mimikyu (2026-10-15)

`import_minior.py` and `import_disguise.py` gave every Minior form and Busted Mimikyu the species icon.
`tools/pwan/stage_minior_mimikyu_icons.py` writes their own icons from the Essentials icons (`MINIOR` for the six Meteor
forms, which look alike in game; `MINIOR_7` ... `MINIOR_13` for the Cores; `MIMIKYU_1`), and redoes the two species
icons: Minior's showed the Red Core (form 0 is the Red Meteor) and Mimikyu's palette turned it olive. The art is placed
where the Gen 7 icons sit, so a form lines up with its species' icon. Rerun it after either importer.

## Icons still missing

The Z-A Megas, the Z Megas, Mega Floette, Mega Meowstic and Mega Magearna still show their species' icon.
