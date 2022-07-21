rm -rf $HOME/.brew
git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew
echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc
source $HOME/.zshrc
brew update
brew install readline