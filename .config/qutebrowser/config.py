import dracula.draw

# Load existing settings made via :set
config.load_autoconfig()

dracula.draw.blood(c, {
    'spacing': {
        'vertical': 6,
        'horizontal': 8
    }
})

c.fonts.default_family = f'"MesloLGS Nerd Font Mono"'
c.fonts.default_size = '14px'
