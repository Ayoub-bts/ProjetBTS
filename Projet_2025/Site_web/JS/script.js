const burgerMenu = document.getElementById('burger-menu');
const navbar = document.getElementById('navbar');

burgerMenu.addEventListener('click', () => {
    navbar.classList.toggle('visible');
    navbar.classList.toggle('hidden');
});

document.querySelector('.btn-grad').addEventListener('click', () => {
    alert('Le fichier des données historiques est en cours de téléchargement.');
});
