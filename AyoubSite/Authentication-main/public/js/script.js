// Sélection des éléments
const burgerMenu = document.getElementById('burger-menu');
const navbar = document.getElementById('navbar');
const body = document.body;

// Gestion du menu burger
burgerMenu.addEventListener('click', () => {
    navbar.classList.toggle('visible');
    navbar.classList.toggle('hidden');

    if (navbar.classList.contains('visible')) {
        body.style.overflow = 'hidden';
    } else {
        body.style.overflow = 'auto';
    }
});

// Navigation fluide (avec correction)
document.querySelectorAll("#navbar a").forEach(link => {
    link.addEventListener("click", function() {
        const targetUrl = this.getAttribute("href");
        window.location.href = targetUrl; // Redirige vers la nouvelle page
    });
});

// Effet sur le menu actif
document.addEventListener("DOMContentLoaded", () => {
    const navLinks = document.querySelectorAll("#navbar a");
    navLinks.forEach(link => {
        if (window.location.href.includes(link.getAttribute("href"))) {
            link.classList.add("active");
        }
    });

    // Charger les données JSON et les afficher
    fetch('../JSON/viticole_dashboard.json')  // Vérifie le chemin exact
        .then(response => {
            if (!response.ok) {
                throw new Error("Erreur lors du chargement du JSON");
            }
            return response.json();
        })
        .then(data => {
            console.log("Données chargées :", data);

            // Afficher le titre du dashboard
            document.getElementById('dashboard-title').innerText = data.title || "Tableau de Bord";

            // Afficher les panneaux du dashboard
            let panelsContainer = document.getElementById('dashboard-panels');
            panelsContainer.innerHTML = ""; // Effacer le contenu existant

            data.panels.forEach(panel => {
                let panelElement = document.createElement("div");
                panelElement.classList.add("panel");
                panelElement.innerHTML = `
                    <h3>${panel.title || "Panel"}</h3>
                    <p>Type: ${panel.type || "Inconnu"}</p>
                    <p>Source: ${panel.datasource?.type || "Non spécifié"}</p>
                `;
                panelsContainer.appendChild(panelElement);
            });
        })
        .catch(error => console.error('Erreur :', error));
});


fetch('http://locahost:8120/donnees')
.catch((error) => console.error(error))
.then(data => {
    console.log('Data : ', data);
})