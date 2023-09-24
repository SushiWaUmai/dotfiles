# Enable Powerlevel10k instant prompt. Should stay close to the top of ~/.zshrc.
# Initialization code that may require console input (password prompts, [y/n]
# confirmations, etc.) must go above this block; everything else may go below.
if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
  source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
fi

source /usr/share/nvm/init-nvm.sh
export PNPM_HOME="$HOME/.local/share/pnpm"
export PATH="$PNPM_HOME:$PATH"
export PATH="$HOME/.local/bin:$PATH"
export GOPATH="$HOME/.go"

export TERM="xterm-256color"
export EDITOR="nvim"
export VISUAL="nvim"

# Disable Telemetry
export DOTNET_CLI_TELEMETRY_OPTOUT=1
export NEXT_TELEMETRY_DISABLED=1

source "${HOME}/.zgenom/zgenom.zsh"

zgenom autoupdate

# if the init script doesn't exist
if ! zgenom saved; then
	echo "Creating a zgenom save"

  # specify plugins here
  zgenom ohmyzsh
	zgenom ohmyzsh plugins/git
	zgenom ohmyzsh plugins/gh
	zgenom ohmyzsh plugins/tmux
	zgenom ohmyzsh plugins/thefuck
	zgenom ohmyzsh plugins/web-search

	zgenom load romkatv/powerlevel10k powerlevel10k

	zgenom load zsh-users/zsh-autosuggestions
	zgenom load zsh-users/zsh-syntax-highlighting
	zgenom load zsh-users/zsh-completions
	zgenom load softmoth/zsh-vim-mode

	zgenom load DarrinTisdale/zsh-aliases-exa
	zgenom load fdellwing/zsh-bat

  # generate the init script from plugins above
  zgenom save
  zgenom compile "$HOME/.zshrc"
fi

# To customize prompt, run `p10k configure` or edit ~/.p10k.zsh.
[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh
